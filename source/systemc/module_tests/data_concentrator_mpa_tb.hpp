/*!
 * @file data_concentrator_mpa_tb.hpp
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

#include <iostream>
#include <sstream>

#include "systemc.h"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../TT_configuration/track_trigger_config.hpp"
#include "../systems/TT_configuration.hpp"
#include "../modules/frontend/data_concentrator.hpp"


/*!
 * @brief
 */
class data_concentrator_mpa_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;
    sc_map_square<sc_signal<bool> > data_valid;
    sc_map_square<sc_signal<data_concentrator::fe_stub_t> > fe_signals;
    sc_signal<data_concentrator::output_t> dc_output;

    // ----- Process Declarations ----------------------------------------------
    void generate_hit_data();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------
    void write_fe(const unsigned int fe_chip, const unsigned int hit_nr,
    		const unsigned int bx, const unsigned int pixel,
            const unsigned int strip, const unsigned int bend);
    void release_fe(const unsigned int fe_chip, const unsigned int hit_nr);

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    data_concentrator dut_data_concentrator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_concentrator_mpa_tb(sc_module_name _name, track_trigger_config configuration);
    SC_HAS_PROCESS(data_concentrator_mpa_tb);
    ~data_concentrator_mpa_tb();

private:
    data_concentrator_config dut_configuration;

    std::ostringstream log_buffer;
};
