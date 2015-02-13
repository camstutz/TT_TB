/*!
 * @file fifo_ctrl.hpp
 * @author Christian Amstutz
 * @date February 13, 2015
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

// ----- Process Declarations --------------------------------------------------
    void read_input_stub();
    void write_AM_stub();
    void update_tag();

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
