/*!
 * @file dtc_input_unit_tb.hpp
 * @author Christian Amstutz
 * @date April 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once


#include "../modules/backend/dtc/dtc_input_unit.hpp"
#include "../systems/TT_configuration.hpp"

#include "../data_formats/gbt_link_format.hpp"
#include "../data_formats/CIC_format/CIC_format.hpp"
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
    sc_map_linear<sc_fifo<dtc_input_unit::output_t> > bx_sorted_outputs;

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
    dtc_input_unit_tb(sc_module_name _name);
    SC_HAS_PROCESS(dtc_input_unit_tb);
    ~dtc_input_unit_tb();

private:
    std::ostringstream log_buffer;
};
