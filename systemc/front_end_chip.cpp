/*!
 * @file front_end_chip.cpp
 * @author Christian Amstutz
 * @date Mar 18, 2014
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
        hit_outputs(MAX_HITS_PER_FE_CHIP, "hit_out", 1),
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
    //* todo: move that to constructor
    SC_THREAD(prioritize_hits);
        sensitive << clk.pos();
    SC_THREAD(write_hits);
        sensitive << selected_stubs.data_written_event();
}

// *****************************************************************************
void front_end_chip::prioritize_hits()
{
    while (1)
    {
        wait();

        fe_out_data::fe_stub_t act_stub;
        int stub_cnt = stub_input.num_available();
        for (int i=0;
                i < std::min(stub_cnt, MAX_HITS_PER_FE_CHIP);
                ++i)
        {
        	//* todo: why does negative edges appear
            //std::cout << sc_time_stamp() << ": %" << std::endl;
            stub_input.read(act_stub);
            selected_stubs.write(act_stub);
        }

        if (stub_input.num_available() >0)
        {
            std::cout << "Warning: Front End Chip received more than 3 hits" << std::endl;
            while(stub_input.nb_read(act_stub))
            {};
        }
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
            hit_outputs.at(i+1).write(hit_to_write);
        }

        wait(clk.posedge_event());

        fe_out_data hit_to_write;
        hit_to_write.set_dv(false);
        hit_to_write.set_data(fe_out_data::fe_stub_t(0,0));
        hit_outputs.write_all(hit_to_write);
    }

}
