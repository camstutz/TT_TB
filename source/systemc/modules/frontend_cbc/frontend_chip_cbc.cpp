/*!
 * @file frontend_chip_cbc.cpp
 * @author Christian Amstutz
 * @date December 15, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "frontend_chip_cbc.hpp"

// *****************************************************************************

// *****************************************************************************

const unsigned int frontend_chip_cbc::max_hits_per_cycle = MAX_HITS_PER_MPA_FE_CHIP;

// *****************************************************************************
frontend_chip_cbc::frontend_chip_cbc(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_input("stub_in"),
        data_valid(MAX_HITS_PER_CBC_FE_CHIP, "data_valid", 0),
        stub_outputs(MAX_HITS_PER_CBC_FE_CHIP, "stub_out", 0),
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

        stub_t act_stub;
        int stub_cnt = stub_input.num_available();
        for (unsigned int i=0;
                i < (unsigned int)std::min(stub_cnt, MAX_HITS_PER_CBC_FE_CHIP);
                ++i)
        {
            stub_input.read(act_stub);
            selected_stubs.write(act_stub);
        }

        if (stub_input.num_available() > 0)
        {
            std::cout << "Warning: CBC Front End Chip received more than "
                      << MAX_HITS_PER_CBC_FE_CHIP << " hits"
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
