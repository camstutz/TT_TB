/*!
 * @file frontend_chip.cpp
 * @author Christian Amstutz
 * @date November 10, 2015
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
        max_stubs_per_cycle(configuration.max_stubs_per_cycle),
        collection_cycles(configuration.collection_cycles),
        total_collected_stubs(configuration.max_stubs_per_cycle * configuration.collection_cycles)
{
    // ----- Process registration ----------------------------------------------
    SC_METHOD(controller);
        sensitive << clk.pos();
        dont_initialize();
    SC_METHOD(read_input);
        sensitive << clk.pos();
        dont_initialize();
    SC_METHOD(write_hits);
        sensitive << clk.pos();
        dont_initialize();

    // ----- Module variable initialization ------------------------------------
    sorted_buffers.resize(2);
    clock_cycle.write(0);
    wbuf_selector.write(0);
    rbuf_selector.write(1);

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void frontend_chip::controller()
{
    int local_clock_cycle = clock_cycle.read();

    if (local_clock_cycle == (int)collection_cycles-1)
    {
        wbuf_selector.write(!wbuf_selector.read());
        rbuf_selector.write(!rbuf_selector.read());
        clock_cycle.write(0);
    }
    else
    {
        clock_cycle.write(local_clock_cycle+1);
    }

    return;
}

// *****************************************************************************
void frontend_chip::read_input()
{
    while (stub_input.num_available() > 0)
    {
        input_stub_t in_stub;
        stub_input.nb_read(in_stub);
        sorted_buffer_stub_t new_stub(clock_cycle, in_stub);
        sorted_buffers[wbuf_selector].insert(new_stub);
    }

    return;
}

// *****************************************************************************
void frontend_chip::write_hits()
{
    data_valid.write(0);
    stub_outputs.write(output_stub_t(output_stub_config));

    if (sorted_buffers[rbuf_selector].size() > 0)
    {
        unsigned int i = 0;
        typename std::set<sorted_buffer_stub_t>::iterator stub_it = sorted_buffers[rbuf_selector].begin();
        while ((sorted_buffers[rbuf_selector].size() > 0) & (i < max_stubs_per_cycle))
        {
            stub stub_to_write(output_stub_config);
            stub_to_write = *stub_it;
            stub_to_write.set_bx(stub_it->get_buffer_bx());

            data_valid.at(i).write(true);
            stub_outputs.at(i).write(stub_to_write);

            sorted_buffers[rbuf_selector].erase(stub_it);
            ++i;
            ++stub_it;
        }

        if ((clock_cycle == (collection_cycles-1)) & (sorted_buffers[rbuf_selector].size() > 0))
        {
            sorted_buffers[rbuf_selector].clear();
            // TODO: put this to log
            std::cerr << sc_time_stamp() << ": Front End Chip received more than "
                      << total_collected_stubs << " hits in " << collection_cycles
                      << " cycles." << std::endl;
        }
    }

    return;
}
