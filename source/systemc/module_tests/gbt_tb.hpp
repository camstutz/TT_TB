/*!
 * @file gbt_tb.hpp
 * @author Christian Amstutz
 * @date April 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/frontend/gbt.hpp"
#include "../data_formats/CIC_format/CIC_format.hpp"
#include "../data_formats/gbt_link_format.hpp"

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
    sc_map_linear<sc_signal<gbt_cbc::frame_t> > input_streams;
    sc_signal<gbt_cbc::output_t> optical_link;

    // ----- Process Declarations ----------------------------------------------
    void generate_cic_data();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    gbt_cbc  gbt_cbc_dut;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    gbt_tb(sc_module_name _name);
    SC_HAS_PROCESS(gbt_tb);
    ~gbt_tb();

private:
    std::ostringstream log_buffer;
};
