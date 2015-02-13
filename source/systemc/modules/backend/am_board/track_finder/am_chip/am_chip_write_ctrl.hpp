/*!
 * @file am_chip_write_ctrl.hpp
 * @author Christian Amstutz
 * @date February 13, 2015
 *
 * @brief File contains the definition of the AM board FSM.
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include "../track_finder_config.hpp"

class am_chip_write_ctrl : public sc_module
{
public:
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;

    /** @brief Data type of the FSM states */
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states RX_HIT;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;

    sc_map_linear<sc_in<superstrip_stream> > hit_inputs;
    sc_map_linear<sc_out<bool> > process_hits;

    /** @brief Signal to enable road processing.
     *
     * Output port of the control signal that shows that in the actual state
     * the hits can be processed.
     */
    sc_out<bool> process_roads;

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
    am_chip_write_ctrl(sc_module_name _name);
    SC_HAS_PROCESS(am_chip_write_ctrl);
};
