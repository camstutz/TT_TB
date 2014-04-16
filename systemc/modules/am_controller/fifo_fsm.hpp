/*!
 * @file fifo_fsm.hpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

/*!
 * @brief
 */
class fifo_fsm : public sc_module
{
public:
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states RX_DATA;
    static const fsm_states STDBY;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_in<bool> fifo_not_empty;
    sc_in<bool> pop;
    sc_out<bool> pok;

    sc_out<bool> fifo_read_en;
    sc_out<bool> reg_en;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<fsm_states> current_state;
    sc_signal<fsm_states> next_state;

    sc_signal<bool> fifo_read_en_d1;

// ----- Process Declarations --------------------------------------------------
    void state_logic();
    void combinatorial();
    void delay_pok();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_fsm(sc_module_name _name);
    SC_HAS_PROCESS(fifo_fsm);
};
