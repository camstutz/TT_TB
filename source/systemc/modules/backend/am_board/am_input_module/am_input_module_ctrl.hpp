/*!
 * @file am_input_module_ctrl.hpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../../systems/TT_configuration.hpp"

#include "../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

// *****************************************************************************

class am_input_module_ctrl : public sc_module
{
public:
    /** @brief Data type of the FSM states */
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states INIT;
    static const fsm_states PROCESS1;
    static const fsm_states PROCESSING;
    static const fsm_states DELETE;

    static const unsigned int layer_nr;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;
    sc_map_linear<sc_in<bool> > frame_available;
    sc_map_linear<sc_in<bool> > frame_empty;
    sc_map_linear<sc_in<bool> > frame_processing;

    sc_out<bool> init_processing;
    sc_out<bool> delete_frame;

// ----- Local Channel Declarations --------------------------------------------
    /** @brief Signal containing the current FSM state. */
    sc_signal<fsm_states> current_state;

// ----- Process Declarations --------------------------------------------------
    void controller();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    am_input_module_ctrl(sc_module_name _name);
    SC_HAS_PROCESS(am_input_module_ctrl);
};
