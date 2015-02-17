/*!
 * @file fifo_ctrl_fsm.hpp
 * @author Christian Amstutz
 * @date February 16, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

/*!
 * @brief
 */
class fifo_ctrl_fsm : public sc_module
{
public:
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states START;
    static const fsm_states PROCESS;
    static const fsm_states WAIT_EVENT_END;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_in<bool> fifo_write_en;
    sc_in<bool> fifo_not_empty;
    sc_in<bool> is_timestamp;
    sc_in<bool> event_active;

    sc_out<bool> event_start;
    sc_out<bool> fifo_read_en;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<fsm_states> current_state;
    sc_signal<fsm_states> next_state;

// ----- Process Declarations --------------------------------------------------
    void state_logic();
    void combinatorial();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_ctrl_fsm(sc_module_name _name);
    SC_HAS_PROCESS(fifo_ctrl_fsm);
};
