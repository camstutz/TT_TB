/*!
 * @file fifo_ctrl.hpp
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

#include "../../../../../data_formats/fm_out_data.hpp"

#include "fifo_ctrl_fsm.hpp"
#include "../../track_finder/track_finder.hpp"

/*!
 * @brief
 */
class fifo_ctrl : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;
    sc_in<bool> fifo_write_en;
    sc_in<bool> fifo_not_empty;
    sc_in<bool> event_active;
    sc_in<fm_out_data> stub_input;

    sc_out<bool> fifo_read_en;
    sc_out<track_finder::hit_stream> stub_output;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<bool> event_start_sig;
    sc_signal<bool> is_timestamp_sig;

// ----- Process Declarations --------------------------------------------------
    void process_stub();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    fifo_ctrl_fsm FSM;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_ctrl(sc_module_name _name);
    SC_HAS_PROCESS(fifo_ctrl);
};
