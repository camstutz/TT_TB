/*!
 * @file am_input_module_tb.hpp
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

#include "../../modules/backend/am_board/am_input_module/am_input_module.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class am_input_module_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<PRBF_2> > frame_in_sigs;
    sc_map_linear<sc_buffer<track_finder::hit_stream> > output_streams;

    // ----- Process Declarations ----------------------------------------------
    void write_frames();
    void print_stream();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    am_input_module dut_am_input_module_tb;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_input_module_tb(sc_module_name _name);
    SC_HAS_PROCESS(am_input_module_tb);
    ~am_input_module_tb();

private:
    std::ostringstream log_buffer;
};
