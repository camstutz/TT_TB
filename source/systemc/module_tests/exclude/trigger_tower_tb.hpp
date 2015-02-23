/*!
 * @file trigger_tower_tb.hpp
 * @author Christian Amstutz
 * @date Jauary 5, 2015
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

#include "../systems/TT_configuration.hpp"
#include "../modules/backend/trigger_tower.hpp"

/*!
 * @brief
 */
class trigger_tower_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<data_organizer::do_in_t> >stream_in;
    sc_map_square<sc_signal<bool> > neighbour_dv_in;
    sc_map_square<sc_signal<fifo_manager::input_stub_t> > neighbour_stub_in;
    sc_map_square<sc_signal<bool> > neighbour_dv_out;
    sc_map_square<sc_signal<fifo_manager::input_stub_t> > neighbour_stub_out;
    sc_map_linear<sc_signal<bool> > road_write_en;
    sc_map_linear<sc_signal<sc_bv<30> > > road_output;


    // ----- Process Declarations ----------------------------------------------
    void write_stream();
    void print_output();

    void test_proc();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    trigger_tower dut_trigger_tower;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    trigger_tower_tb(sc_module_name _name);
    SC_HAS_PROCESS(trigger_tower_tb);
    ~trigger_tower_tb();

private:
    std::ostringstream log_buffer;
};
