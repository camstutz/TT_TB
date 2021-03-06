/*!
 * @file hit_buffer_write_ctrl.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../../../systems/TT_configuration.hpp"
#include "hit_buffer_write_ctrl_config.hpp"

#include "../../simple_stream_protocol.hpp"
#include "sc_map.hpp"

#include <systemc.h>

class hit_buffer_write_ctrl : public sc_module
{
public:
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;

    /** @brief Data type of the FSM states */
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states RX_HIT;

    const unsigned int layer_nr;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;

    sc_map_linear<sc_in<superstrip_stream> > hit_inputs;
    sc_map_linear<sc_out<bool> > process_hits;
    sc_out<bool> event_begin;
    sc_out<bool> event_end;

// ----- Local Channel Declarations --------------------------------------------
    /** @brief Signal containing the current FSM state. */
    sc_signal<fsm_states> current_state;

// ----- Process Declarations --------------------------------------------------
    /**
     * @brief Combinatorial process of the FSM
     *
     * Switches through the different states depending on the input ports
     * write_enable and road_buffer_empty. Updates the output ports
     * process_roads and write_roads.
     *
     * This process runs indefinitely and is sensitive to the change of the
     * current state, the empty signal of the output road buffer, and the write
     * enable inputs.
     */
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
    hit_buffer_write_ctrl(sc_module_name _name, const hit_buffer_write_ctrl_config configuration);
    SC_HAS_PROCESS(hit_buffer_write_ctrl);
};
