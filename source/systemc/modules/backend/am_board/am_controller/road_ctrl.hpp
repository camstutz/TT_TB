/*!
 * @file road_ctrl.hpp
 * @author Christian Amstutz
 * @date December 15, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
class road_ctrl : public sc_module
{
public:

    // TODO: numbers to constants

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;
    sc_in<bool> init;
    sc_in<bool> data_ready_road;
    sc_in<sc_bv<AM_BOARD_PATTERN_WIDTH> > event_tag;
    sc_in<sc_bv<AM_BOARD_ROAD_WIDTH> > road_in;

    sc_out<bool> finish_road;
    sc_out<bool> write_en_road;
    sc_out<sc_bv<30> > road_out;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<bool> write_en_sig;
    sc_signal<sc_bv<AM_BOARD_ROAD_WIDTH> > road_sig;
	sc_signal<bool> data_ready_last;

// ----- Process Declarations --------------------------------------------------
    void transfer_roads();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    road_ctrl(sc_module_name _name);
    SC_HAS_PROCESS(road_ctrl);
};
