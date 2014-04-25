/*!
 * @file fifo_manager_controller.hpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../../TT_configuration.hpp"

/*!
 * @brief
 */
class fifo_manager_controller : public sc_module
{
public:
    typedef unsigned int fsm_states;
//    static const fsm_states IDLE;
//    static const fsm_states RX_DATA;
//    static const fsm_states STDBY;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    /** Input port for the reset signal (currently not used) */
    sc_in<bool> rst;

    sc_map_linear<sc_out<bool>> buffer_write_en;
    sc_map_linear<sc_out<unsigned int>> buffer_read_en;
    sc_out<unsigned int> time_stamp;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<fsm_states> current_state;
    sc_signal<fsm_states> next_state;

// ----- Process Declarations --------------------------------------------------
    void state_logic();
    void fsm_logic();
    void update_timestamp();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager_controller(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager_controller);
};
