/*!
 * @file am_board_tb.hpp
 * @author Christian Amstutz
 * @date Apr 7, 2014
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

#include "../systemc/modules/am_board/am_board.hpp"

/*!
 * @brief
 */
class am_board_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> reset;
    sc_signal<sc_bv<3> > init_event;
    sc_map_linear<sc_signal<bool> > write_en;
    sc_map_linear<sc_signal<am_board::pattern_t> > patterns;
    sc_signal<bool> ready_to_process;
    sc_signal<bool> road_ready;
    sc_signal<am_board::road_addr_t> road;

    // ----- Process Declarations ----------------------------------------------
    void create_input();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    am_board DUT;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_board_tb(sc_module_name _name);
    SC_HAS_PROCESS(am_board_tb);
    ~am_board_tb();

private:
    std::ostringstream log_buffer;
};
