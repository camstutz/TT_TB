/*!
 * @file am_controller.hpp
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

#include "../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../../systems/TT_configuration.hpp"
#include "../../../../data_formats/fm_out_data.hpp"

#include "../track_finder/track_finder.hpp"
#include "fifo_ctrl/fifo_ctrl.hpp"
#include "read_ctrl_fsm.hpp"


/*!
 * @brief SystemC
 */
class am_controller : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<bool> > fifo_not_empty;
    sc_map_linear<sc_in<bool> > fifo_write_en;
    sc_map_linear<sc_in<fm_out_data> > stub_inputs;

    sc_map_linear<sc_out<bool> > fifo_read_en;
    sc_map_linear<sc_out<track_finder::hit_stream> > stub_outputs;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> event_start_sig;
    sc_signal<bool> transmission_start_sig;
    sc_signal<bool> event_active_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<fifo_ctrl> fifo_controller_array;
    read_ctrl_fsm read_controller;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_controller(const sc_module_name _name);
};
