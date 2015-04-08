/*!
 * @file data_concentrator_cbc_tb.hpp
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
#include "../modules/frontend_cbc/data_concentrator_cbc.hpp"


/*!
 * @brief
 */
class data_concentrator_cbc_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_square<sc_signal<bool> > data_valid;
    sc_map_square<sc_signal<data_concentrator_cbc::fe_stub_t> > fe_signals;
    sc_signal<data_concentrator_cbc::output_t> dc_output;

    // ----- Process Declarations ----------------------------------------------
    void generate_hit_data();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------
    void write_fe(const unsigned int fe_chip, const unsigned int hit_nr,
            const unsigned int address, const unsigned int bend);
    void release_fe(const unsigned int fe_chip, const unsigned int hit_nr);

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    data_concentrator_cbc dut_data_concentrator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_concentrator_cbc_tb(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator_cbc_tb);
    ~data_concentrator_cbc_tb();

private:
    std::ostringstream log_buffer;
};
