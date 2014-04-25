/*!
 * @file am_system_tb.hpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
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

#include "../systemc/TT_configuration.hpp"
#include "../systemc/data_representations/do_out_data.hpp"
#include "../systemc/modules/stub_fifo/stub_fifo.hpp"
#include "../systemc/modules/am_controller/am_controller.hpp"
#include "../systemc/modules/am_board/am_board.hpp"

/*!
 * @brief
 */
class am_system_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> reset;
    sc_map_linear<sc_signal<bool> > write_en;
    sc_map_linear<sc_signal<do_out_data> > input_stubs;
    sc_map_linear<sc_signal<bool> > fifo_not_empty;
    sc_map_linear<sc_signal<bool> > fifo_read_en;
    sc_map_linear<sc_signal<do_out_data> > fifo_stubs;
    sc_signal<sc_bv<3> > init_event;
    sc_map_linear<sc_signal<bool> > am_write_en;
    sc_map_linear<sc_signal<sc_bv<18> > > am_stubs;
    sc_signal<bool> am_data_ready;
    sc_signal<sc_bv<21> > am_road;
    sc_signal<bool> road_write_en;
    sc_signal<sc_bv<21> > output_road;

    // ----- Process Declarations ----------------------------------------------
    void create_input();
    void detect_roads();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    sc_map_linear<stub_fifo<12> > input_fifos;
    am_controller am_ctrl;
    am_board pattern_reco_board;

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
