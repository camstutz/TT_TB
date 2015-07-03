/*!
 * @file data_organizer_tb.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/processor_organizer/processor_organizer.hpp"
#include "../../TT_configuration/track_trigger_config.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class processor_organizer_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<processor_organizer::do_input_t> > do_input_sigs;
    sc_map_square<sc_buffer<processor_organizer::processor_output_t> > processor_output_sigs;

    // ----- Process Declarations ----------------------------------------------
    void write_frames();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    processor_organizer dut_processor_organizer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    processor_organizer_tb(sc_module_name _name, track_trigger_config configuration);
    SC_HAS_PROCESS(processor_organizer_tb);
    ~processor_organizer_tb();

private:
    std::ostringstream log_buffer;
};
