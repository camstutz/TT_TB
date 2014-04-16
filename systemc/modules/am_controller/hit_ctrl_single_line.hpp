/*!
 * @file hit_ctrl_single_line.hpp
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

//#include "../../../lib/systemc_helpers/sc_map/sc_map.hpp"

//#include "../../TT_configuration.hpp"
#include "../../data_representations/do_out_data.hpp"

/*!
 * @brief
 */
class hit_ctrl_single_line : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;
    sc_in<bool> new_hit;
    sc_in<bool> wr_hit_lamb;
    sc_in<sc_bv<3> > init_event;
    sc_in<do_out_data> stub_input;

    sc_out<bool> hee_reg;
    sc_out<bool> write_en;
    sc_out<sc_bv<18> >  stub_output;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<do_out_data> stub_read;

// ----- Process Declarations --------------------------------------------------
    void read_input_stub();
    void write_AM_stub();
    void update_hee_reg();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_ctrl_single_line(sc_module_name _name);
    SC_HAS_PROCESS(hit_ctrl_single_line);
};
