/*!
 * @file hit_buffer_output_ctrl.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../simple_stream_protocol.hpp"
#include "hit_buffer_output_ctrl_config.hpp"
#include "../../../../../systems/TT_configuration.hpp"

#include "sc_map.hpp"

#include <systemc.h>

// *****************************************************************************
class hit_buffer_output_ctrl : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;

    /** @brief Data type of the FSM states */
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states START;
    static const fsm_states TX_ROAD;

    const unsigned int layer_nr;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;
    sc_in<bool> start_transmission;

    sc_map_linear<sc_fifo_in<hit_t> > hit_input;
    sc_map_linear<sc_out<hit_stream> > hit_output;

// ----- Local Channel Declarations --------------------------------------------
    /** @brief Signal containing the current FSM state. */
    sc_signal<fsm_states> current_state;

// ----- Process Declarations --------------------------------------------------
    void controller();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * @brief Constructor
     *
     * Naming of all the SystemC ports and signals. Creating processes and
     * assigning their sensitivity lists. Initializes the FSM by setting the
     * current state to IDLE.
     */
    hit_buffer_output_ctrl(sc_module_name _name, const hit_buffer_output_ctrl_config configuration);
    SC_HAS_PROCESS(hit_buffer_output_ctrl);
};
