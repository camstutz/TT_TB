/*!
 * @file dtc.cpp
 * @author Christian Amstutz
 * @date April 27, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc.hpp"

// *****************************************************************************

const unsigned int dtc::input_nr = 3;

const unsigned int dtc::collection_cycles = NR_DC_WINDOW_CYCLES;

// *****************************************************************************

/*!
 * @class dtc
 * The module is sensitive to ...
 */

dtc::dtc(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        gbt_inputs(input_nr, "gbt_input"),
        tower_output("tower_output"),
        bx_sorted_buffer(input_nr, 2, collection_cycles, "bx_sorted_inputs"),
        relative_bx_sig("bx_sig"),
        read_buffer_sig("read_buffer_sig"),
        write_buffer_sig("write_buffer_sig"),
        tower_output_sig("tower_output_sig"),
        controller("controller"),
        input_units(input_nr, "input_unit"),
        output_unit("output_unit"),
        delay_output("delay_output")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    controller.clk.bind(clk);
    controller.bunch_crossing.bind(relative_bx_sig);
    controller.read_buffer.bind(read_buffer_sig);
    controller.write_buffer.bind(write_buffer_sig);

    unsigned int input_id = 0;
    sc_map_linear<dtc_input_unit>::iterator input_unit_it = input_units.begin();
    for (; input_unit_it != input_units.end(); ++input_unit_it)
    {
        input_unit_it->clk.bind(clk);
        input_unit_it->gbt_input.bind(gbt_inputs[input_id]);
        input_unit_it->write_buffer_select.bind(write_buffer_sig);
        input_unit_it->bx_buffer_out.bind(bx_sorted_buffer(input_id, input_id, 0, sc_map::max, 0, sc_map::max));

        ++input_id;
    }

    output_unit.clk.bind(clk);
    output_unit.relative_bx.bind(relative_bx_sig);
    output_unit.read_buffer.bind(read_buffer_sig);
    output_unit.bx_buffer_inputs.bind(bx_sorted_buffer);
    output_unit.tower_out_stream.bind(tower_output_sig);

    delay_output.clk.bind(clk);
    delay_output.input.bind(tower_output_sig);
    delay_output.delayed.bind(tower_output);

    return;
}
