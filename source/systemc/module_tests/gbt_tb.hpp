/*!
 * @file gbt_tb.hpp
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

#include "../modules/frontend/gbt.hpp"
#include "../modules/frontend/data_concentrator_config.hpp"
#include "../data_formats/CIC_frame/CIC_frame.hpp"
#include "../data_formats/gbt_link_format.hpp"

#include "../modules/frontend/gbt_config.hpp"
#include "../systems/TT_configuration.hpp"
#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class gbt_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<gbt::input_t> > input_streams;
    sc_signal<gbt::output_t> optical_link;

    // ----- Process Declarations ----------------------------------------------
    void generate_cic_data();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    gbt  gbt_dut;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    gbt_tb(sc_module_name _name, gbt_config configuration, data_concentrator_config CBC_concentrator_config);
    SC_HAS_PROCESS(gbt_tb);
    ~gbt_tb();

private:
    gbt_config dut_configuration;
    data_concentrator_config CBC_concentrator_config;

    std::ostringstream log_buffer;
};
