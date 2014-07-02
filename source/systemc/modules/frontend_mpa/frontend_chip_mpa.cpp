/*!
 * @file frontend_chip_mpa.cpp
 * @author Christian Amstutz
 * @date July 2, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "frontend_chip_mpa.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip
 *
 * The module is sensitive to ....
 */

frontend_chip_mpa::frontend_chip_mpa(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        en("en"),
        stub_input("stub_input"),
        data_valids(MAX_HITS_PER_MPA_FE_CHIP, "data_valid", 0),
        stub_outputs(MAX_HITS_PER_MPA_FE_CHIP, "stub_output", 0),
        selected_stubs("selected_stubs", MAX_HITS_PER_MPA_FE_CHIP)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(prioritize_hits);
        sensitive << clk.pos();
    SC_THREAD(write_hits);
        sensitive << clk.pos();
        //sensitive << selected_stubs.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void frontend_chip_mpa::prioritize_hits()
{
    while (1)
    {
        wait();

        fe_mpa_stub_t act_stub;
        int stub_cnt = stub_input.num_available();
        for (int i=0;
                i < std::min(stub_cnt, MAX_HITS_PER_MPA_FE_CHIP);
                ++i)
        {
            stub_input.read(act_stub);
            selected_stubs.write(act_stub);
        }

        if (stub_input.num_available() > 0)
        {
            std::cout << "Warning: MPA Front End Chip received more than "
                      << MAX_HITS_PER_MPA_FE_CHIP << " hits" << std::endl;
            while(stub_input.nb_read(act_stub))
            {};
        }
    }

}

// *****************************************************************************
void frontend_chip_mpa::write_hits()
{
    while (1)
    {
        wait();

        bool data_valid = false;
        fe_mpa_stub_t stub_to_write(0,0,0,0);

        // todo: optimization potential if not written every cycle
        stub_outputs.write_all(stub_to_write);

        unsigned int num_stubs = selected_stubs.num_available();
        for (unsigned int i=0; i<num_stubs; i++)
        {
            data_valids.at(i).write(true);
            stub_outputs.at(i).write(selected_stubs.read());
        }
    }

}
