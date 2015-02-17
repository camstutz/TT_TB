/*!
 * @file am_chip_read_ctrl.hpp
 * @author Christian Amstutz
 * @date February 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include "../track_finder_config.hpp"

class am_chip_read_ctrl : public sc_module
{
public:
    typedef simple_stream_protocol<road_t> road_stream;

    /** @brief Data type of the FSM states */
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states START;
    static const fsm_states TX_ROAD;

// ----- Port Declarations -----------------------------------------------------
    /** @brief Clock
     *
     * Input port for the clock signal.
     */
    sc_in<bool> clk;
    sc_in<bool> roads_detected;

    sc_fifo_in<road_t> road_input;
    sc_out<road_stream> road_output;

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
    am_chip_read_ctrl(sc_module_name _name);
    SC_HAS_PROCESS(am_chip_read_ctrl);
};
