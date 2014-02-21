/*!
 * @file front_end_chip.cpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "front_end_chip.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip
 *
 * The module is sensitive to ....
 */

front_end_chip::front_end_chip(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        en("en"),
        stub_input("stub_in"),
        hit_outputs(MAX_HITS_PER_FE_CHIP, "hit_out"),
        selected_stubs("sel_stubs", MAX_HITS_PER_FE_CHIP)
{
    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void front_end_chip::end_of_elaboration()
{
    SC_THREAD(prioritize_hits);
        sensitive << stub_input.data_written_event();
    SC_THREAD(write_hits);
        sensitive << selected_stubs.data_written_event();
}

// *****************************************************************************
void front_end_chip::prioritize_hits()
{
    while(1)
    {
        wait();
        if(!clk.posedge())
        {
            wait(clk.posedge_event());
        }

        stub act_stub;
        for(int i=0;
                i <= std::min(stub_input.num_available(), MAX_HITS_PER_FE_CHIP);
                i++)
        {
            stub_input.nb_read(act_stub);
            selected_stubs.nb_write(act_stub);
        }
        while(stub_input.nb_read(act_stub))
        {};
    }

}

// *****************************************************************************
void front_end_chip::write_hits()
{
    while (1)
    {
        wait();

        unsigned int num_stubs = selected_stubs.num_available();
        for (unsigned int i=0; i<num_stubs; i++)
        {
            fe_out_data hit_to_write;
            hit_to_write.set_dv(true);
            hit_to_write.set_data(selected_stubs.read());
            hit_outputs.at(i).write(hit_to_write);
        }

        wait(clk.posedge_event());

        //* todo: write parallel to all ports when implemented in map
        for(auto& output : hit_outputs)
        {
            fe_out_data hit_to_write;
            hit_to_write.set_dv(false);
            hit_to_write.set_data(stub(0,0));
            output.write(hit_to_write);
        }
    }

}
