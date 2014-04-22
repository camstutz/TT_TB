/*!
 * @file hit_ctrl.hpp
 * @author Christian Amstutz
 * @date Apr 20, 2014
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
#include "../../data_representations/do_out_data.hpp"
#include "hit_ctrl_single_line.hpp"

/*!
 * @brief
 */
class hit_ctrl : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;
    sc_map_linear<sc_in<bool> > new_hit;
    sc_map_linear<sc_in<bool> > wr_hit_lamb;
    sc_in<sc_bv<3> > init_event;
    sc_map_linear<sc_in<do_out_data>> stub_inputs;

    sc_map_linear<sc_out<bool>> hee_reg_before;
    sc_map_linear<sc_out<bool>> hee_reg;
    sc_map_linear<sc_out<bool>> write_en;
    sc_map_linear<sc_out<sc_bv<18>>> stub_output;
    sc_out<sc_bv<16>> event_tag;

// ----- Local Channel Declarations --------------------------------------------
    sc_map_linear<sc_signal<sc_bv<16>>> tag_signals;

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    sc_map_linear<hit_ctrl_single_line> hit_controllers;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_ctrl(sc_module_name _name);
    SC_HAS_PROCESS(hit_ctrl);
};
