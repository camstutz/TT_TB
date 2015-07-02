/*!
 * @file data_organizer_tb.hpp
 * @author Christian Amstutz
 * @date April 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/data_organizer/data_organizer.hpp"
#include "../../TT_configuration/track_trigger_config.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class data_organizer_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<data_organizer::dtc_input_t> > dtc_input_sigs;
    sc_map_linear<sc_buffer<data_organizer::proc_unit_output_t> > proc_output_sigs;

    // ----- Process Declarations ----------------------------------------------
    void write_frames();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    data_organizer dut_data_organizer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer_tb(sc_module_name _name, track_trigger_config configuration);
    SC_HAS_PROCESS(data_organizer_tb);
    ~data_organizer_tb();

private:
    std::ostringstream log_buffer;
};
