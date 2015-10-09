/*!
 * @file dtc_output_unit_tb.hpp
 * @author Christian Amstutz
 * @date July 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/backend/dtc/dtc_buffer_element.hpp"
#include "../modules/backend/dtc/dtc_output_unit.hpp"
#include "../modules/backend/dtc/dtc_controller.hpp"

#include "../TT_configuration/track_trigger_config.hpp"

#include "../data_formats/prbf/PRBF.hpp"

#include "sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class dtc_output_unit_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_cube<sc_fifo<dtc_buffer_element> > bx_sorted_inputs;
    sc_buffer<dtc_output_unit::output_t> tower_output;
    sc_signal<unsigned int> bx_sig;
    sc_signal<unsigned int> read_buffer_sig;
    sc_signal<unsigned int> write_buffer_sig;

    // ----- Process Declarations ----------------------------------------------
    void fill_FIFOs();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    dtc_controller dut_dtc_controller;
    dtc_output_unit dut_dtc_output_unit;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc_output_unit_tb(sc_module_name _name, const track_trigger_config& configuration);
    SC_HAS_PROCESS(dtc_output_unit_tb);
    ~dtc_output_unit_tb();

private:
    std::ostringstream log_buffer;
};
