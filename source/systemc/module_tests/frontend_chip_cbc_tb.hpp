/*!
 * @file frontend_chip_cbc_tb.hpp
 * @author Christian Amstutz
 * @date July 28, 2015
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
#include "../modules/frontend/frontend_chip.hpp"

/*!
 * @brief
 */
class frontend_chip_cbc_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_fifo<frontend_chip::input_stub_t> stub_input_sig;
    sc_map_linear<sc_signal<bool> > data_valid_signals;
    sc_map_linear<sc_signal<frontend_chip
    ::output_stub_t> > fe_out_signals;

    // ----- Process Declarations ----------------------------------------------
    void generate_stubs();
    void analyse_FE_out();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    frontend_chip dut_front_end_chip;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip_cbc_tb(sc_module_name _name, sc_trace_file* trace_file, track_trigger_config configuration);
    SC_HAS_PROCESS(frontend_chip_cbc_tb);
    ~frontend_chip_cbc_tb();

private:
    std::ostringstream log_buffer;

    void trace(sc_trace_file* trace_file);
    void write_stub(unsigned int strip, int bend);
};
