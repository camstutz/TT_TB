/*!
 * @file frontend_chip_cbc.cpp
 * @author Christian Amstutz
 * @date February 17, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "frontend_chip_cbc.hpp"

// *****************************************************************************

// *****************************************************************************

const unsigned int frontend_chip_cbc::max_input_hits = MAX_HITS_PER_CBC_FE_CHIP;
const unsigned int frontend_chip_cbc::max_hits_per_cycle = MAX_HITS_PER_MPA_FE_CHIP;

// *****************************************************************************
frontend_chip_cbc::frontend_chip_cbc(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_input("stub_in"),
        data_valid(max_input_hits, "data_valid", 0),
        stub_outputs(max_input_hits, "stub_out", 0),
        selected_stubs("sel_stubs", MAX_HITS_PER_CBC_FE_CHIP)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(prioritize_hits);
        sensitive << clk.pos();
    SC_THREAD(write_hits);
        sensitive << selected_stubs.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void frontend_chip_cbc::prioritize_hits()
{
    while (1)
    {
        wait();

        // Read only the first 'max_input_hits' number of hits
        stub_t act_stub;
        unsigned int stub_cnt = stub_input.num_available();
        for (unsigned int i=0; i < std::min(stub_cnt, max_input_hits); ++i)
        {
            stub_input.read(act_stub);
            selected_stubs.write(act_stub);
        }

        if (stub_input.num_available() > 0)
        {
            std::cout << "Warning: CBC Front End Chip received more than "
                      << max_input_hits << " hits"
                      << " @ " << sc_time_stamp() << std::endl;
            while(stub_input.nb_read(act_stub))
            {};
        }
    }

}

// *****************************************************************************
void frontend_chip_cbc::write_hits()
{
    while (1)
    {
        wait();

        while (selected_stubs.num_available() > 0)
        {
            unsigned int i = 0;
            while ((i < max_hits_per_cycle) && (selected_stubs.num_available() > 0))
            {
            	data_valid.at(i).write(true);
            	stub_outputs.at(i).write(selected_stubs.read());
                ++i;
            }

            wait(clk.posedge_event());

            data_valid.write_all(0);
            stub_outputs.write_all(stub_t(0,0));
        }
    }

}
