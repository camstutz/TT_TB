/*!
 * @file frontend_chip_mpa_tb.hpp
 * @author Christian Amstutz
 * @date July 4, 2014
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

#include "../libraries/systemc_helpers/sc_map/sc_map_linear.hpp"

#include "../systems/TT_configuration.hpp"
#include "../modules/frontend_mpa/frontend_chip_mpa.hpp"

/*!
 * @brief
 */
class frontend_chip_mpa_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> en_sig;
    sc_fifo<frontend_chip_mpa::fe_mpa_stub_t> stub_input_sig;
    sc_map_linear<sc_signal<bool> > data_valid_signals;
    sc_map_linear<sc_signal<frontend_chip_mpa::fe_mpa_stub_t> > fe_out_signals;

    // ----- Process Declarations ----------------------------------------------
    void generate_stubs();
    void analyse_FE_out();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    frontend_chip_mpa dut_front_end_chip;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip_mpa_tb(sc_module_name _name);
    SC_HAS_PROCESS(frontend_chip_mpa_tb);
    ~frontend_chip_mpa_tb();
    void end_of_elaboration();

private:
    std::ostringstream log_buffer;
};
