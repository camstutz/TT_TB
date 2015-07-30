/*!
 * @file dtc_input_unit_tb.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/backend/dtc/dtc_buffer_element.hpp"
#include "../modules/backend/dtc/dtc_input_unit.hpp"
#include "../TT_configuration/track_trigger_config.hpp"
#include "../systems/TT_configuration.hpp"

#include "../data_formats/gbt_link_format.hpp"
#include "../data_formats/CIC_frame/CIC_frame.hpp"
#include "../data_formats/prbf/PRBF.hpp"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class dtc_input_unit_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_buffer<dtc_input_unit::input_t> gbt_input_link;
    sc_buffer<unsigned int> write_buffer_select_sig;
    sc_map_square<sc_fifo<dtc_buffer_element> > bx_sorted_outputs;

    // ----- Process Declarations ----------------------------------------------
    void generate_packets();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    dtc_input_unit dut_dtc_input_unit;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc_input_unit_tb(sc_module_name _name, track_trigger_config configuration);
    SC_HAS_PROCESS(dtc_input_unit_tb);
    ~dtc_input_unit_tb();

private:
    dtc_input_unit_config dut_configuration;

    std::ostringstream log_buffer;
};
