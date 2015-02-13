/*!
 * @file am_board.hpp
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

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../../systems/TT_configuration.hpp"
#include "../../../data_formats/fm_out_data.hpp"
#include "stub_fifo/stub_fifo.hpp"
#include "am_controller/am_controller.hpp"
#include "track_finder/track_finder.hpp"


/*!
 * @brief SystemC
 */
class am_board : public sc_module
{
public:
    typedef fm_out_data fifo_in_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;

    sc_map_linear<sc_in<bool> > fifo_write_en;
    sc_map_linear<sc_in<fifo_in_t> > fifo_inputs;

    sc_out<bool> road_write_en;
    sc_out<sc_bv<30> > road_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<bool> > fifo_not_empty_sig;
    sc_map_linear<sc_signal<bool> > fifo_read_en_sig;
    sc_map_linear<sc_signal<fifo_in_t> > fifo_stub_out_sig;
    sc_signal<sc_bv<3> > init_ev_sig;
    sc_map_linear<sc_signal<bool> > am_write_en_sig;
    sc_map_linear<sc_signal<sc_bv<AM_BOARD_PATTERN_WIDTH> > > am_pattern_sig;
    sc_signal<bool> am_data_ready_sig;
    sc_signal<sc_bv<AM_BOARD_ROAD_WIDTH> > am_road_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<stub_fifo<STUB_FIFO_DEPTH> > stub_fifo_array;
    am_controller AMcontroller;
    track_finder TrackFinder;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_board(const sc_module_name _name);
};
