/*!
 * @file frontend_chip_mpa_tb.hpp
 * @author Christian Amstutz
 * @date December 19, 2014
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
    sc_fifo<frontend_chip_mpa::input_stub_t> stub_input_sig;
    sc_map_linear<sc_signal<bool> > data_valid_signals;
    sc_map_linear<sc_signal<frontend_chip_mpa::output_stub_t> > fe_out_signals;

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
    frontend_chip_mpa_tb(sc_module_name _name, sc_trace_file* trace_file);
    SC_HAS_PROCESS(frontend_chip_mpa_tb);
    ~frontend_chip_mpa_tb();

private:
    std::ostringstream log_buffer;

    void trace(sc_trace_file* trace_file);
    void write_stub(frontend_chip_mpa::input_stub_t::bx_t bx, frontend_chip_mpa::input_stub_t::pixel_t pixel,
            frontend_chip_mpa::input_stub_t::strip_t strip, frontend_chip_mpa::input_stub_t::bend_t bend);
};
