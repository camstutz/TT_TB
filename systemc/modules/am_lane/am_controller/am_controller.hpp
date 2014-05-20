/*!
 * @file am_controller.hpp
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

#include "../../../../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../TT_configuration.hpp"
#include "../../../data_representations/fm_out_data.hpp"
#include "main_fsm.hpp"
#include "fifo_fsm.hpp"
#include "hit_ctrl.hpp"
#include "road_ctrl.hpp"


/*!
 * @brief SystemC
 */
class am_controller : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> init;
    sc_map_linear<sc_in<bool> > fifo_not_empty;
    sc_map_linear<sc_in<fm_out_data> > stub_inputs;
    sc_in<bool> data_ready;
    sc_in<sc_bv<21> > road_in;

    sc_out<sc_bv<3> > init_ev;
    sc_map_linear<sc_out<bool> > fifo_read_en;
    sc_map_linear<sc_out<bool> > am_write_en;
    sc_map_linear<sc_out<sc_bv<18> > > am_stub_outputs;
    sc_out<bool> road_write_en;
    sc_out<sc_bv<30> > road_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<bool> > pop_sig;
    sc_map_linear<sc_signal<bool> > pok_sig;
    sc_map_linear<sc_signal<bool> > hit_ctrl_reg_en;
    sc_map_linear<sc_signal<bool> > hee_reg_sig;
    sc_map_linear<sc_signal<bool> > hee_reg_before_sig;
    sc_map_linear<sc_signal<bool> > hit_ctrl_en;
    sc_signal<bool> road_ctrl_finish_road;
    sc_signal<sc_bv<16> > event_tag_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    main_fsm main_am_fsm;
    sc_map_linear<fifo_fsm> fifo_fsm_array;
    hit_ctrl hit_controller;
    road_ctrl road_controller;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_controller(const sc_module_name _name);
    SC_HAS_PROCESS(am_controller);

};
