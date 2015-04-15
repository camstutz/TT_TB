/*!
 * @file dtc_output_unit.cpp
 * @author Christian Amstutz
 * @date April 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_output_unit.hpp"

// *****************************************************************************

const unsigned int dtc_output_unit::fe_collect_cycles = NR_DC_WINDOW_CYCLES;

// *****************************************************************************

/*!
 * @class dtc_output_unit
 *
 * The module is sensitive to ...
 */

dtc_output_unit::dtc_output_unit(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        bunch_crossing("bunch_crossing"),
        read_buffer("read_buffer"),
        write_buffer("write_buffer"),
        bx_sorted_stubs(fe_collect_cycles, "bx_sorted_stubs"),
        tower_out_stream("tower_out_stream")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << clk.pos();
    SC_THREAD(generate_frame);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    output_buffer.resize(2);
    output_buffer[0].resize(8);
    output_buffer[1].resize(8);

    return;
}

// *****************************************************************************
void dtc_output_unit::read_input()
{
    while (1)
    {
        wait();

        if (bunch_crossing.read() == 0)
        {
            for (unsigned bx = 0; bx < fe_collect_cycles; ++bx)
            {
                output_buffer[write_buffer][bx].clear();
                while (bx_sorted_stubs[bx].num_available() > 0)
                {
                    output_buffer[write_buffer][bx].push_back(bx_sorted_stubs[bx].read());
                }
            }
        }
    }
}

// *****************************************************************************
void dtc_output_unit::generate_frame()
{
    while (1)
    {
        wait();

        PRBF_0 output_frame(bunch_crossing);
        while (!output_buffer[read_buffer][bunch_crossing].empty())
        {
            PRBF_0::stub_element_t stub_element = output_buffer[read_buffer][bunch_crossing].back();
            output_frame.add_stub(stub_element);
            output_buffer[read_buffer][bunch_crossing].pop_back();
        }

        if (output_frame.get_trailer().get_stub_count() > 0)
        {
            tower_out_stream.write(output_frame);
        }
    }

}
