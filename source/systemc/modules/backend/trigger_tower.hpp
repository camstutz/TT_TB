/*!
 * @file trigger_tower.hpp
 * @author Christian Amstutz
 * @date February 19, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"

#include "data_organizer/data_organizer.hpp"
#include "fifo_manager/fifo_manager.hpp"
#include "am_board/am_board.hpp"

/*!
 * @brief
 */
class trigger_tower : public sc_module
{
public:
    //typedef data_organizer_one_layer::do_in_t do_in_t;
    //typedef data_organizer_one_layer::do_out_t do_out_t;

	static const unsigned int number_neighbour_towers;
	static const unsigned int number_AM_boards;
	static const unsigned int detector_layers;
	static const unsigned int nr_DO_out_stubs;

    const unsigned int phi;
    const unsigned int z;

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk_LHC;
    sc_in<bool> clk_x4;
    sc_in<bool> clk_AM;

    /** Linear sc_map for the stream inputs. There exist a separate input for
     * every layer of the detector */
    sc_map_linear<sc_in<data_organizer::do_in_t> >stream_in;

    /** Inputs for the data valid signals of the neighboring trigger towers. The
     *  dimensions of sc_map are (tower, layer). */
    sc_map_square<sc_in<bool> > neighbour_dv_in;
    /** Inputs for the stubs from the neighboring trigger towers. The dimensions
     *  of sc_map are (tower, layer). */
    sc_map_square<sc_in<fifo_manager::input_stub_t> > neighbour_stub_in;
    /** Outputs for the data valid signals of the neighboring trigger towers.
     *  The dimensions of sc_map are (tower, layer). */
    sc_map_square<sc_out<bool> > neighbour_dv_out;
    /** Outputs for the stubs from the neighboring trigger towers. The
     *  dimensions of sc_map are (tower, layer). */
    sc_map_square<sc_out<fifo_manager::input_stub_t> > neighbour_stub_out;

    sc_map_square<sc_out<track_finder::hit_stream> > road_output;

// ----- Local Channel Declarations --------------------------------------------
    sc_map_square<sc_signal<bool> > do_dv_sigs;
    sc_map_square<sc_signal<data_organizer::do_out_t> > do_stub_out_sigs;

    sc_map_square<sc_signal<bool> > am_fifo_write_en_sigs;
    sc_map_square<sc_signal<am_board::fifo_in_t> > am_fifo_input_sigs;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    data_organizer dataOrganizer;
    fifo_manager fifoManager;
    sc_map_linear<am_board> am_board_array;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    trigger_tower(sc_module_name _name, unsigned int phi, unsigned int z);
    SC_HAS_PROCESS(trigger_tower);
};
