/*!
 * @file dtc.cpp
 * @author Christian Amstutz
 * @date April 15, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc.hpp"

// *****************************************************************************

const unsigned int dtc::input_nr = 1;

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
        bx_sorted_inputs(NR_DC_WINDOW_CYCLES, "bx_sorted_inputs"),
        bx_sig("bx_sig"),
        read_buffer_sig("read_buffer_sig"),
        write_buffer_sig("write_buffer_sig"),
        controller("controller"),
        input_units(input_nr, "input_unit"),
        output_unit("output_unit")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    controller.clk.bind(clk);
    controller.bunch_crossing.bind(bx_sig);
    controller.read_buffer.bind(read_buffer_sig);
    controller.write_buffer.bind(write_buffer_sig);

    sc_map_linear<dtc_input_unit>::iterator input_unit_it = input_units.begin();
    sc_map_linear<sc_in<input_t> >::iterator gbt_input_it = gbt_inputs.begin();
    for (; input_unit_it != input_units.end(); ++input_unit_it)
    {
        input_unit_it->clk.bind(clk);
        input_unit_it->gbt_input.bind(*gbt_input_it);
        input_unit_it->bx_sorted_stubs.bind(bx_sorted_inputs);

        ++gbt_input_it;
    }

    output_unit.clk.bind(clk);
    output_unit.bunch_crossing.bind(bx_sig);
    output_unit.read_buffer.bind(read_buffer_sig);
    output_unit.write_buffer.bind(write_buffer_sig);
    output_unit.bx_sorted_stubs.bind(bx_sorted_inputs);
    output_unit.tower_out_stream.bind(tower_output);

    return;
}
