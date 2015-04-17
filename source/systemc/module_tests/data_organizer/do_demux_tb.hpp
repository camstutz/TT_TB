/*!
 * @file do_demux_tb.hpp
 * @author Christian Amstutz
 * @date April 16, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/data_organizer/do_demux.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class do_demux_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_buffer<do_demux::bunch_crossing_t> bunch_crossing_request_sig;
    sc_fifo<do_demux::input_t> stub_input_sig;
    sc_map_linear<sc_buffer<do_demux::output_t> > proc_unit_output_sigs;

    // ----- Process Declarations ----------------------------------------------
    void write_stubs();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    do_demux dut_do_demux;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    do_demux_tb(sc_module_name _name);
    SC_HAS_PROCESS(do_demux_tb);
    ~do_demux_tb();

private:
    std::ostringstream log_buffer;
};
