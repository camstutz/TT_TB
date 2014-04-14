/*!
 * @file am_board_fsm.hpp
 * @author Christian Amstutz
 * @date Apr 10, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../../TT_configuration.hpp"

/*!
 * @brief
 */

class am_board_fsm : public sc_module
{
public:
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states RX_HIT;
    static const fsm_states PROCESS_ROAD;
    static const fsm_states WRITE_ROAD;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_linear<sc_in<bool> > write_en;
    sc_in<bool> road_buffer_empty;

    sc_out<bool> next_pattern_ready;
    sc_out<bool> process_roads;
    sc_out<bool> write_roads;



// ----- Local Channel Declarations --------------------------------------------
    sc_signal<fsm_states> state;

// ----- Process Declarations --------------------------------------------------
    void fsm();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    am_board_fsm(sc_module_name _name);
    SC_HAS_PROCESS(am_board_fsm);

private:
    bool one_write_en_active();
};


