/*!
 * @file frontend_chip.cpp
 * @author Christian Amstutz
 * @date July 30, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "frontend_chip.hpp"

// *****************************************************************************

// *****************************************************************************

frontend_chip::frontend_chip(const sc_module_name _name,
        frontend_chip_config configuration) :
        sc_module(_name),
        input_stub_config(configuration.input_stub),
        output_stub_config(configuration.output_stub),
        clk("clk"),
        stub_input("stub_input"),
        data_valid(configuration.max_stubs_per_cycle, "data_valid", 0),
        stub_outputs(configuration.max_stubs_per_cycle, "stub_output", 0),
        selected_stubs("selected_stubs", configuration.max_stubs_per_cycle * configuration.collection_cycles),
        max_stubs_per_cycle(configuration.max_stubs_per_cycle),
        collection_cycles(configuration.collection_cycles),
        total_collected_stubs(configuration.max_stubs_per_cycle * configuration.collection_cycles)
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
void frontend_chip::read_input()
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
            input_stub_t act_stub(input_stub_config);
            act_stub = stub_input.read();
            collection_buffer[clock_cycle].push_back(act_stub);
        }

        if (clock_cycle == (int)collection_cycles-1)
        {
            prioritize_hits();
            clock_cycle = -1;
        }
    }
}

// *****************************************************************************
void frontend_chip::write_hits()
{
    while (1)
    {
        wait();

        while (selected_stubs.num_available() > 0)
        {
            unsigned int i = 0;
            while ((i < max_stubs_per_cycle) && (selected_stubs.num_available() > 0))
            {
                data_valid.at(i).write(true);
                stub stub_to_write(output_stub_config);
                stub_to_write = selected_stubs.read();
                stub_outputs.at(i).write(stub_to_write);
                ++i;
            }

            wait(clk.posedge_event());

            data_valid.write(0);
            stub_outputs.write(output_stub_t(output_stub_config));
        }
    }

}

// *****************************************************************************
void frontend_chip::prioritize_hits()
{
    ordered_stubs.clear();

    /* read all the stubs received in the last cycles and store them ordered by
     * the bend into a map */
    for (unsigned int cycle = 0; cycle < collection_cycles; ++cycle)
    {
        while (!collection_buffer[cycle].empty())
        {
            output_stub_t act_stub(input_stub_config);
            act_stub = collection_buffer[cycle].back();
            collection_buffer[cycle].pop_back();
            act_stub.set_bx(cycle);
            ordered_stubs.insert(typename ordering_buffer_t::value_type(act_stub.get_bend(), act_stub));
        }
    }

    typename ordering_buffer_t::reverse_iterator output_stub_it = ordered_stubs.rbegin();
    for (unsigned int i = 0; i < total_collected_stubs; ++i)
    {
        if (output_stub_it !=  ordered_stubs.rend())
        {
            selected_stubs.write(output_stub_it->second);
            ++output_stub_it;
        }
    }

    if (output_stub_it != ordered_stubs.rend())
    {
        // TODO: put this to log
        std::cerr << sc_time_stamp() << ": Front End Chip received more than "
                  << total_collected_stubs << " hits in " << collection_cycles
                  << " cycles." << std::endl;
    }
}
