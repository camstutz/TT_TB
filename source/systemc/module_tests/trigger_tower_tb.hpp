/*!
 * @file trigger_tower_tb.hpp
 * @author Christian Amstutz
 * @date April 21, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/backend/data_organizer/data_organizer.hpp"
#include "../systems/TT_configuration.hpp"
#include "../modules/backend/trigger_tower.hpp"
#include "../data_formats/prbf/PRBF.hpp"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class trigger_tower_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_square<sc_buffer<PRBF_0> > dtc_input_sigs;
    sc_map_cube<sc_buffer<am_board::output_stream_t> > hit_output_sigs;

    // ----- Process Declarations ----------------------------------------------
    void write_stream();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    trigger_tower dut_trigger_tower;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    trigger_tower_tb(sc_module_name _name);
    SC_HAS_PROCESS(trigger_tower_tb);
    ~trigger_tower_tb();

private:
    std::ostringstream log_buffer;
};