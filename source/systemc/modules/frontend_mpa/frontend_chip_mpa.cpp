/*!
 * @file frontend_chip_mpa.cpp
 * @author Christian Amstutz
 * @date December 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "frontend_chip_mpa.hpp"

// *****************************************************************************

// *****************************************************************************

const unsigned int frontend_chip_mpa::max_hits_per_cycle = MAX_HITS_PER_MPA_FE_CHIP;
const unsigned int frontend_chip_mpa::collection_cycles = COLLECTION_CYCLES_MPA_FE_CHIP;
const unsigned int frontend_chip_mpa::total_hits = MAX_HITS_PER_MPA_FE_CHIP * COLLECTION_CYCLES_MPA_FE_CHIP;

// *****************************************************************************
frontend_chip_mpa::frontend_chip_mpa(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        stub_input("stub_input"),
        data_valid(max_hits_per_cycle, "data_valid", 0),
        stub_outputs(max_hits_per_cycle, "stub_output", 0),
        selected_stubs("selected_stubs", total_hits)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << clk.pos();
    SC_THREAD(write_hits);
        sensitive << selected_stubs.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void frontend_chip_mpa::read_input()
{
    collection_buffer.resize(collection_cycles);

    wait();
    int clock_cycle = -1;

    while (1)
    {
        wait();
        ++clock_cycle;

        while (stub_input.num_available() > 0)
        {
            stub_t act_stub;
            stub_input.read(act_stub);
            collection_buffer[clock_cycle].push_back(act_stub);
        }

        if (clock_cycle == collection_cycles-1)
        {
            prioritize_hits();
            clock_cycle = -1;
        }
    }
}

// *****************************************************************************
void frontend_chip_mpa::write_hits()
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
            stub_outputs.write_all(stub_t(0,0,0,0));
        }
    }

}

// *****************************************************************************
void frontend_chip_mpa::prioritize_hits()
{
    /* read all the stubs receiced in the last cycles and store them ordered by
     * the bend into a map */
    std::multimap<stub_t::bend_t, stub_t> ordered_stubs;
    for (unsigned int cycle = 0; cycle < collection_cycles; ++cycle)
    {
        while (!collection_buffer[cycle].empty())
        {
            stub_t act_stub = collection_buffer[cycle].back();
            act_stub.set_bx(cycle);
            ordered_stubs.insert(std::pair<stub_t::bend_t, stub_t>(act_stub.get_bend(), act_stub));
            collection_buffer[cycle].pop_back();
        }
    }

    std::multimap<stub_t::bend_t, stub_t>::reverse_iterator output_stub_it = ordered_stubs.rbegin();
    for (unsigned int i = 0; i < total_hits; ++i)
    {
        if (output_stub_it !=  ordered_stubs.rend())
        {
            selected_stubs.write(output_stub_it->second);
            ++output_stub_it;
        }
    }

    if (output_stub_it !=  ordered_stubs.rend())
    {
        std::cerr << "Warning: MPA Front End Chip received more than "
                  << total_hits << " hits in " << collection_cycles
                  << " cycles @ " << sc_time_stamp() << std::endl;
    }
}
