/*!
 * @file am_chip_tb.hpp
 * @author Christian Amstutz
 * @date April 23, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/am_board/track_finder/am_chip/am_chip.hpp"
#include "../../modules/backend/am_board/track_finder/pattern_bank/pattern_bank.hpp"

#include "../../TT_configuration/track_trigger_config.hpp"
//#include "../../systems/TT_configuration.hpp"

#include "sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class am_chip_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<am_chip::superstrip_stream> > hit_input_sigs;
    sc_buffer<am_chip::road_stream> road_output_sig;

    // ----- Process Declarations ----------------------------------------------
    void write_streams();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    pattern_bank patterns;
    am_chip dut_AM_chip;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_chip_tb(sc_module_name _name, track_trigger_config configuration);
    SC_HAS_PROCESS(am_chip_tb);
    ~am_chip_tb();

private:
    std::ostringstream log_buffer;
};
