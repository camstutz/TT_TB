/*!
 * @file fifo_fsm.hpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
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
    typedef enum fsm_states {
        IDLE = 0x01,
        RX_DATA = 0x02,
        STDBY = 0x03
    } fsm_states;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_in<bool> fifo_empty;
    sc_in<bool> pop;

    sc_out<bool> fifo_read_en;
    sc_out<bool> reg_en;

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
    fifo_fsm(sc_module_name _name);
    SC_HAS_PROCESS(fifo_fsm);
};
