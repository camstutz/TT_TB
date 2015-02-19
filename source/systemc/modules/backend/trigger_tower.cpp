/*!
 * @file trigger_tower.cpp
 * @author Christian Amstutz
 * @date February 19, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower.hpp"

// *****************************************************************************

const unsigned int trigger_tower::number_neighbour_towers = NR_NEIGHBOURING_TOWERS;
const unsigned int trigger_tower::number_AM_boards = NR_AM_BOARDS;
const unsigned int trigger_tower::detector_layers = NR_DETECTOR_LAYERS;
const unsigned int trigger_tower::nr_DO_out_stubs = NR_DO_OUT_STUBS;

// *****************************************************************************
trigger_tower::trigger_tower(const sc_module_name _name, unsigned int phi, unsigned int z) :
		phi(phi),
		z(z),
		clk_LHC("clk_LHC"),
		clk_x4("clk_x4"),
		clk_AM("clk_AM"),
		stream_in(detector_layers, "stream_in"),
		neighbour_dv_in(number_neighbour_towers, detector_layers, "neighbour_dv_in"),
		neighbour_stub_in(number_neighbour_towers, detector_layers, "neighbour_stub_in"),
		neighbour_dv_out(number_neighbour_towers, detector_layers, "nighbour_dv_out"),
		neighbour_stub_out(number_neighbour_towers, detector_layers, "neighbour_stub_out"),
		road_output(number_AM_boards, detector_layers, "road_output"),
		do_dv_sigs(detector_layers, nr_DO_out_stubs, "do_dv_sigs"),
		do_stub_out_sigs(detector_layers, nr_DO_out_stubs, "do_stub_out_sigs"),
		am_fifo_write_en_sigs(number_AM_boards, detector_layers, "am_fifo_write_en_sigs"),
		am_fifo_input_sigs(number_AM_boards, detector_layers, "am_fifo_input_sigs"),
		dataOrganizer("dataOrganizer", phi, z),
		fifoManager("fifoManager"),
		am_board_array(number_AM_boards, "AM_board_array")
{
	dataOrganizer.clk.bind(clk_LHC);
	dataOrganizer.stream_in.bind(stream_in);
	dataOrganizer.dv.bind(do_dv_sigs);
	dataOrganizer.stub_out.bind(do_stub_out_sigs);

	fifoManager.clk.bind(clk_x4);
	fifoManager.dv_in.bind(do_dv_sigs);
	fifoManager.stub_in.bind(do_stub_out_sigs);
	fifoManager.neighbour_dv_in.bind(neighbour_dv_in);
	fifoManager.neighbour_stub_in.bind(neighbour_stub_in);
	fifoManager.neighbour_dv_out.bind(neighbour_dv_out);
	fifoManager.neighbour_stub_out.bind(neighbour_stub_out);
	fifoManager.dv_out.bind(am_fifo_write_en_sigs);
	fifoManager.fifo_out.bind(am_fifo_input_sigs);

    unsigned int am_cnt = 0;
    sc_map_linear<am_board>::iterator am_board_it = am_board_array.begin();
    for (; am_board_it != am_board_array.end(); ++am_board_it)
    {
    	am_board_it->clk.bind(clk_AM);
    	am_board_it->clk_fifo(clk_x4);
    	sc_map_square<sc_signal<bool> >::square_iterator write_en_it = am_fifo_write_en_sigs.begin_partial(am_cnt, false, 0, true);
    	am_board_it->fifo_write_en.bind_by_iter(write_en_it);
    	sc_map_square<sc_signal<am_board::fifo_in_t> >::square_iterator fifo_sig_it = am_fifo_input_sigs.begin_partial(am_cnt, false, 0, true);
    	am_board_it->fifo_inputs.bind_by_iter(fifo_sig_it);
    	sc_map_square<sc_out<track_finder::hit_stream> >::square_iterator road_output_it = road_output.begin_partial(am_cnt, false, 0, true);
    	am_board_it->hit_output.bind_by_iter(road_output_it);

    	++am_cnt;
    }

	return;
}
