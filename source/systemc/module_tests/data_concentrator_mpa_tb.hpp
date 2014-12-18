/*!
 * @file data_concentrator_mpa_tb.hpp
 * @author Christian Amstutz
 * @date July 7, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <sstream>

#include "systemc.h"

#include "../libraries/systemc_helpers/sc_map/sc_map_square.hpp"

#include "../systems/TT_configuration.hpp"
#include "../modules/frontend_mpa/data_concentrator_mpa.hpp"


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
    sc_map_square<sc_signal<data_concentrator_mpa::in_stub_t> > fe_signals;
    sc_signal<data_concentrator_mpa::out_t> dc_output;

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
    data_concentrator_mpa dut_data_concentrator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_concentrator_mpa_tb(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator_mpa_tb);
    ~data_concentrator_mpa_tb();

private:
    std::ostringstream log_buffer;
};
