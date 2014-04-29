/*!
 * @file main_fsm.hpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../TT_configuration.hpp"

/*!
 * @brief
 */
class main_fsm : public sc_module
{
public:
    static const unsigned int am_latency;

    typedef unsigned int fsm_states;
    static const fsm_states RESET;
    static const fsm_states RX_HIT;
    static const fsm_states WAIT_T0;
    static const fsm_states SEND_ROAD;
    static const fsm_states SEND_INIT_EVENT;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_in<bool> init;
    sc_map_linear<sc_in<bool> > pok;
    sc_map_linear<sc_in<bool> > hee_reg;
    sc_map_linear<sc_in<bool> > hee_reg_before;
    sc_in<bool> finish_road;

    sc_map_linear<sc_out<bool> > pop;
    sc_map_linear<sc_out<bool> > en;
    sc_out<sc_bv<3> > init_ev;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<fsm_states> current_state;
    sc_signal<fsm_states> next_state;

    sc_signal<unsigned int> AM_latency_cnt;

// ----- Process Declarations --------------------------------------------------
    void state_logic();
    void combinatorial();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    main_fsm(sc_module_name _name);
    SC_HAS_PROCESS(main_fsm);
};
