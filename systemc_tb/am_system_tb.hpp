/*!
 * @file am_system_tb.hpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
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

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"

//#include "../systemc/TT_configuration.hpp"
#include "../systemc/stub_fifo.hpp"
#include "../systemc/fifo_fsm.hpp"

/*!
 * @brief
 */
class am_system_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;

    // ----- Process Declarations ----------------------------------------------
    void create_input();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    sc_map_linear<stub_fifo<12> > input_fifos;
    sc_map_linear<fifo_fsm> fifo_fsms;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_system_tb(sc_module_name _name);
    SC_HAS_PROCESS(am_system_tb);
    ~am_system_tb();

private:
    std::ostringstream log_buffer;
};
