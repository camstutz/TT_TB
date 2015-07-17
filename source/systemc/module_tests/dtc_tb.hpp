/*!
 * @file dtc_tb.hpp
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


#include "../modules/backend/dtc/dtc.hpp"

#include "../data_formats/gbt_link_format.hpp"
#include "../data_formats/CIC_format/CIC_format.hpp"
#include "../data_formats/prbf/PRBF.hpp"

#include "../TT_configuration/track_trigger_config.hpp"
#include "../systems/TT_configuration.hpp"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class dtc_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<dtc_input_unit::input_t> > gbt_input_links;
    sc_buffer<dtc::output_t> tower_output_stream;

    // ----- Process Declarations ----------------------------------------------
    void generate_packets();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    dtc dut_dtc;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc_tb(sc_module_name _name, track_trigger_config configuration);
    SC_HAS_PROCESS(dtc_tb);
    ~dtc_tb();

private:
    std::ostringstream log_buffer;
};
