/*!
 * @file am_chip_fsm.hpp
 * @author Christian Amstutz
 * @date May 5, 2014
 *
 * @brief File contains the definition of the AM board FSM.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../../systems/TT_configuration.hpp"

/*!
 * @brief FSM that controls the AM board.
 *
 * The FSM sequences the reading of the hits, the processing of the data and the
 * writing of the detected roads.
 *
 * Description of the states:
 *
 * IDLE: The FSM is in this state while the AM board is ready to receive new
 * hits. If there is some hit detected, the FSM goes to state RX_HIT.
 *
 * RX_HIT: Receive hits - in this state the AM board reads all the hits into the
 * board. If there is no hit on any layer received, then the FSM goes to the
 * PROCESS_ROAD state.
 *
 * PROCESS_ROAD: The AM board is processing the read hits and creates the roads.
 * This state lasts in this implementation for only one cycle, then the FSM goes
 * to the WRITE_ROAD state.
 *
 * WRITE_ROAD: In the write road state. The AM board writes out all the detected
 * roads. This state lasts until no more roads are in the buffer and then the
 * state goes to idle.
 *
 * \dot
   digraph finite_state_machine {
     size = "8,5"
     node [shape = doublecircle];
     IDLE;
     node [shape = circle];
     IDLE -> IDLE;
     IDLE -> RX_HIT [label="one_write_en_active"];
     RX_HIT -> RX_HIT [label="one_write_en_active"];
     RX_HIT -> PROCESS_ROAD;
     PROCESS_ROAD -> WRITE_ROAD;
     WRITE_ROAD -> WRITE_ROAD;
     WRITE_ROAD -> IDLE [label="road_buffer_empty"];
   }
 * \enddot
 */

class am_chip_fsm : public sc_module
{
public:
    /** @brief Data type of the FSM states */
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states RX_HIT;
    static const fsm_states PROCESS_ROAD;
    static const fsm_states WRITE_ROAD;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;

    /** @brief Reset (not used)
     *
     * Input port for the reset signal.
     */
    sc_in<bool> rst;

    /** @brief Hit write enable signals.
     *
     * Array of input ports for the write enable signals of the incoming hits to
     * the AM board. There is one port for each layer on which hits can be detected.
     */
    sc_map_linear<sc_in<bool> > write_en;

    /** @brief Road buffer emtpy signal
     *
     * Input port for the control signal that indicates whether the output road
     * buffer is empty or not. The signal is true when the buffer is empty.
     */
    sc_in<bool> road_buffer_empty;

    /** @brief Signal to enable road processing.
     *
     * Output port of the control signal that shows that in the actual state
     * the hits can be processed.
     */
    sc_out<bool> process_roads;

    /** @brief Signal to enable writing of roads.
     *
     * Output port for the control signal that controls the writing of the
     * roads off the AM board.
     */
    sc_out<bool> write_roads;

// ----- Local Channel Declarations --------------------------------------------
    /** @brief Signal containing the current FSM state. */
    sc_signal<fsm_states> current_state;

    /** @brief Signal containing the FSM state for the next clock cycle. */
    sc_signal<fsm_states> next_state;

// ----- Process Declarations --------------------------------------------------
    /**
     * @brief Updates the next state synchronously
     *
     * This process runs indefinitely and is sensitive to the positive edge of
     * the clock.
     */
    void state_logic();

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
    void combinatorial();

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
    am_chip_fsm(sc_module_name _name);
    SC_HAS_PROCESS(am_chip_fsm);

private:
    /** @brief Checks if at least one write enable input is active
     *
     * All the write enable inputs to the FSM are tested and if at least one of
     * them is active (true), the function returns true.
     */
    bool one_write_en_active();
};
