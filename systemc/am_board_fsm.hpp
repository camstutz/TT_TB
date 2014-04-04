/*!
 * @file am_board_fsm.hpp
 * @author Christian Amstutz
 * @date Apr 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "TT_configuration.hpp"

/*!
 * @brief
 */
class am_board_fsm : public sc_module
{
public:
    typedef enum fsm_states {
        IDLE    = 0x01,
        RX_HIT  = 0x02,
        LD_ROAD = 0x03,
        TX_WAIT = 0x04,
        TX_ROAD = 0x05,
    } fsm_states;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_in<sc_bv<NR_DETECTOR_LAYERS> > write_en;

    sc_out<bool> scan_arrray;
    sc_out<bool> road_ld;
    sc_out<bool> road_tx;
    sc_out<bool> output_reg_init;

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
};
