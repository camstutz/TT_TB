/*!
 * @file am_lane.hpp
 * @author Christian Amstutz
 * @date Apr 28, 2014
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
#include "../../data_representations/fm_out_data.hpp"
#include "am_controller/am_controller.hpp"
#include "am_board/am_board.hpp"
#include "stub_fifo/stub_fifo.hpp"

/*!
 * @brief SystemC
 */
class am_lane : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_map_linear<sc_in<fm_out_data> > fifo_inputs;

    sc_out<bool> road_write_en;
    sc_out<sc_bv<30> > road_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<bool> > fifo_not_empty_sig;
    sc_map_linear<sc_signal<bool> > fifo_read_en_sig;
    sc_map_linear<sc_signal<fm_out_data> > fifo_stub_out_sig;
    sc_signal<sc_bv<3> > init_ev_sig;
    sc_map_linear<sc_signal<bool> > am_write_en_sig;
    sc_map_linear<sc_signal<sc_bv<18> > > am_pattern_sig;
    sc_signal<bool> am_data_ready_sig;
    sc_signal<sc_bv<21> > am_road_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<stub_fifo<STUB_FIFO_DEPTH> > stub_fifo_array;
    am_controller AMcontroller;
    am_board AMboard;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_lane(const sc_module_name _name);
    SC_HAS_PROCESS(am_lane);

};
