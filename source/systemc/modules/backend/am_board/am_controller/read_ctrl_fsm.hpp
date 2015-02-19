/*!
 * @file read_ctrl_fsm.hpp
 * @author Christian Amstutz
 * @date February 18, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../../systems/TT_configuration.hpp"
#include "../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

/*!
 * @brief
 */
class read_ctrl_fsm : public sc_module
{
public:
    typedef unsigned int fsm_states;
    static const fsm_states IDLE;
    static const fsm_states INIT_EVENT;
    static const fsm_states START_TRANS;
    static const fsm_states PROCESS;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_map_linear<sc_in<bool> > fifo_not_empty;
    sc_map_linear<sc_in<bool> > fifo_write_en;
    sc_map_linear<sc_in<bool> > layers_active;

    sc_out<bool> event_start;
    sc_out<bool> transmission_start;
    sc_out<bool> event_active;

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
    read_ctrl_fsm(sc_module_name _name);
    SC_HAS_PROCESS(read_ctrl_fsm);

private:
    sc_bv<NR_DETECTOR_LAYERS> active_layer_array;
};
