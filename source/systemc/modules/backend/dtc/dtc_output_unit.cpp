/*!
 * @file dtc_output_unit.cpp
 * @author Christian Amstutz
 * @date July 17, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_output_unit.hpp"

// *****************************************************************************

/*!
 * @class dtc_output_unit
 *
 * The module is sensitive to ...
 */

dtc_output_unit::dtc_output_unit(sc_module_name _name,
        const dtc_output_unit_config& configuration) :
        sc_module(_name),
        dtc_input_nr(configuration.dtc_input_nr),
        fe_collect_cycles(configuration.fe_collect_cycles),
        clk("clk"),
        relative_bx("relative_bx"),
        read_buffer("read_buffer"),
        bx_buffer_inputs(dtc_input_nr, 2, fe_collect_cycles, "bx_buffer_input"),
        tower_out_stream("tower_out_stream")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_frame);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void dtc_output_unit::generate_frame()
{
    while (1)
    {
        wait();

        output_t::header_t::bunch_crossing_ID_t bx;
        output_t output_frame;
        for (unsigned int input_id = 0; input_id < dtc_input_nr; ++input_id)
        {
            sc_fifo_in<dtc_buffer_element>& bx_buffer = bx_buffer_inputs.at(input_id, read_buffer.read(), relative_bx.read());
            while (bx_buffer.num_available() > 0)
            {
                dtc_buffer_element stub_element;
                stub_element= bx_buffer.read();
                output_frame.add_stub(stub_element.second);
                bx = stub_element.first;
            }
        }

        if (output_frame.stub_count() > 0)
        {
            output_frame.set_bunch_crossing(bx);
            tower_out_stream.write(output_frame);

            SYSTEMC_LOG << "Frame " << output_frame.get_bunch_crossing()
                    << " with " << output_frame.stub_count() << " stubs transmitted.";
        }
    }

}
