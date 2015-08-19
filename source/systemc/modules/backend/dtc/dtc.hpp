/*!
 * @file dtc.hpp
 * @author Christian Amstutz
 * @date August 19, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_input_unit.hpp"
#include "dtc_output_unit.hpp"
#include "dtc_controller.hpp"
#include "dtc_buffer_element.hpp"

#include "dtc_config.hpp"

#include "sc_map.hpp"
#include "sc_delay_signal.hpp"

#include "systemc.h"

/*!
 * @brief
 */
class dtc : public sc_module
{
public:
    typedef dtc_input_unit::input_t input_t;
    typedef dtc_output_unit::output_t output_t;

    const unsigned int input_nr;
    const unsigned int collection_cycles;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<input_t> > gbt_inputs;
    sc_out<output_t> tower_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_cube<sc_fifo<dtc_buffer_element> > bx_sorted_buffer;
    sc_signal<unsigned int> relative_bx_sig;
    sc_signal<unsigned int> read_buffer_sig;
    sc_signal<unsigned int> write_buffer_sig;
    sc_buffer<output_t> tower_output_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    dtc_controller controller;
    sc_map_linear<dtc_input_unit> input_units;
    dtc_output_unit output_unit;
    sc_delay_signal<output_t> delay_output;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc(sc_module_name _name, dtc_config configuration);
};
