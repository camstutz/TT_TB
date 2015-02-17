/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "tt_tb.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(tt_tb);
#endif

// *****************************************************************************

/*!
 * @class sensor_module
 *
 */

tt_tb::tt_tb(const sc_module_name _name) :
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        LHCx4_clock("LHCx4_clock", 6.25, SC_NS, 0.5, 25, SC_NS, true),
        AM_clock("AM_clock", 10, SC_NS, 0.5, 25, SC_NS, true),
        hit_fifos_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo_mpa", 0, 0, 0, 0),
        hit_fifos_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo_cbc", NR_DETECTOR_MPA_LAYERS, 0, 0, 0),
        fe_signals(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "fe_signals"),
        result_write_en(NR_TRIGGER_TOWERS, NR_AM_BOARDS, "result_write_en"),
        result_road(NR_TRIGGER_TOWERS, NR_AM_BOARDS, "result_road"),
        hit_cnt_sig("hit_cnt_sig"),
        neighbour_dv_sig(NR_TOWER_CONNECTIONS, NR_DETECTOR_LAYERS, 2, "neighbour_dv_sig"),
        neighbour_stub_sig(NR_TOWER_CONNECTIONS, NR_DETECTOR_LAYERS, 2, "neighbour_stub_sig"),
        hitGenerator("Hit_Generator", "data/hits.txt"),
        sensor_modules_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor_module_mpa", 0, 0, 0),
        sensor_modules_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor_module_cbc", NR_DETECTOR_MPA_LAYERS, 0, 0),
        trigger_tower_0_0("trigger_tower_0_0", 0, 0),
        trigger_tower_0_1("trigger_tower_0_1", 0, 1),
        trigger_tower_1_0("trigger_tower_1_0", 1, 0),
        trigger_tower_1_1("trigger_tower_1_1", 1, 1)
        //roadAnalyzer("road_analyzer")
{
    hitGenerator.mpa_stub_outputs.bind(hit_fifos_mpa);
    hitGenerator.cbc_stub_outputs.bind(hit_fifos_cbc);
    hitGenerator.hit_cnt(hit_cnt_sig);

    sc_map_cube<sensor_module_mpa>::iterator module_mpa_it = module_mpa_it = sensor_modules_mpa.begin();
    for (; module_mpa_it != sensor_modules_mpa.end(); ++module_mpa_it)
    {
        std::pair<bool, sc_map_cube<sensor_module_mpa>::full_key_type> full_key;
        full_key = sensor_modules_mpa.get_key(*module_mpa_it);

        module_mpa_it->clk.bind(LHC_clock);
        sc_map_4d<sc_fifo<hit_generator::mpa_stub_t> >::_4d_iterator fifo_it  = hit_fifos_mpa.begin_partial(full_key.second.Z_dim, false, full_key.second.Y_dim, false, full_key.second.X_dim, false, 0, true);
        module_mpa_it->stub_inputs.bind_by_iter(fifo_it);
        module_mpa_it->dc_out.bind(fe_signals.at(full_key.second.Z_dim, full_key.second.Y_dim, full_key.second.X_dim));
    }

    sc_map_cube<sensor_module_cbc>::iterator module_cbc_it = module_cbc_it = sensor_modules_cbc.begin();
    for (; module_cbc_it != sensor_modules_cbc.end(); ++module_cbc_it)
    {
        std::pair<bool, sc_map_cube<sensor_module_cbc>::full_key_type> full_key;
        full_key = sensor_modules_cbc.get_key(*module_cbc_it);

        module_cbc_it->clk.bind(LHC_clock);
        sc_map_4d<sc_fifo<hit_generator::cbc_stub_t> >::_4d_iterator fifo_it  = hit_fifos_cbc.begin_partial(full_key.second.Z_dim, false, full_key.second.Y_dim, false, full_key.second.X_dim, false, 0, true);
        module_cbc_it->stub_inputs.bind_by_iter(fifo_it);
        module_cbc_it->dc_out.bind(fe_signals.at(full_key.second.Z_dim, full_key.second.Y_dim, full_key.second.X_dim));
    }

// Trigger Tower 0-0
    trigger_tower_0_0.clk_LHC.bind(LHC_clock);
    trigger_tower_0_0.clk_x4.bind(LHCx4_clock);
    trigger_tower_0_0.clk_AM.bind(AM_clock);
    sc_map_cube<sc_signal<data_organizer::do_in_t > >::cube_iterator fe_stream_it_0_0 = fe_signals.begin_partial(0, true, 0, false, 0, false);
    trigger_tower_0_0.stream_in.bind_by_iter(fe_stream_it_0_0);

    sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_0_0_a = neighbour_dv_sig.begin_partial(0, false, 0, true, 0, false);
    sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_0_0_a = trigger_tower_0_0.neighbour_dv_in.begin_partial(0, false, 0, true);
    trigger_tower_0_0.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_0_0_a, neighbour_dv_sig_in_it_0_0_a);
    sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_0_0_a = neighbour_dv_sig.begin_partial(0, false, 0, true, 1, false);
    sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_0_0_a = trigger_tower_0_0.neighbour_dv_out.begin_partial(0, false, 0, true);
    trigger_tower_0_0.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_0_0_a, neighbour_dv_sig_out_it_0_0_a);
    sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_0_0_b = neighbour_dv_sig.begin_partial(1, false, 0, true, 1, false);
    sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_0_0_b = trigger_tower_0_0.neighbour_dv_in.begin_partial(1, false, 0, true);
    trigger_tower_0_0.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_0_0_b, neighbour_dv_sig_in_it_0_0_b);
    sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_0_0_b = neighbour_dv_sig.begin_partial(1, false, 0, true, 0, false);
    sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_0_0_b = trigger_tower_0_0.neighbour_dv_out.begin_partial(1, false, 0, true);
    trigger_tower_0_0.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_0_0_b, neighbour_dv_sig_out_it_0_0_b);

    sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_0_0_a = neighbour_stub_sig.begin_partial(0, false, 0, true, 0, false);
    sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_0_0_a = trigger_tower_0_0.neighbour_stub_in.begin_partial(0, false, 0, true);
    trigger_tower_0_0.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_0_0_a, neighbour_stub_sig_in_it_0_0_a);
    sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_0_0_a = neighbour_stub_sig.begin_partial(0, false, 0, true, 1, false);
    sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_0_0_a = trigger_tower_0_0.neighbour_stub_out.begin_partial(0, false, 0, true);
    trigger_tower_0_0.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_0_0_a, neighbour_stub_sig_out_it_0_0_a);
    sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_0_0_b = neighbour_stub_sig.begin_partial(1, false, 0, true, 1, false);
    sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_0_0_b = trigger_tower_0_0.neighbour_stub_in.begin_partial(1, false, 0, true);
    trigger_tower_0_0.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_0_0_b, neighbour_stub_sig_in_it_0_0_b);
    sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_0_0_b = neighbour_stub_sig.begin_partial(1, false, 0, true, 0, false);
    sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_0_0_b = trigger_tower_0_0.neighbour_stub_out.begin_partial(1, false, 0, true);
    trigger_tower_0_0.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_0_0_b, neighbour_stub_sig_out_it_0_0_b);
    sc_map_square<sc_signal<bool> >::square_iterator result_write_en_it_0_0 = result_write_en.begin_partial(0, false, 0, true);
    trigger_tower_0_0.road_write_en.bind_by_iter(result_write_en_it_0_0);
    sc_map_square<sc_signal<track_finder::hit_stream > >::square_iterator result_road_it_0_0 = result_road.begin_partial(0, false, 0, true);
    trigger_tower_0_0.road_output.bind_by_iter(result_road_it_0_0);


// Trigger Tower 0-1
	trigger_tower_0_1.clk_LHC.bind(LHC_clock);
	trigger_tower_0_1.clk_x4.bind(LHCx4_clock);
	trigger_tower_0_1.clk_AM.bind(AM_clock);
	sc_map_cube<sc_signal<data_organizer::do_in_t > >::cube_iterator fe_stream_it_0_1 = fe_signals.begin_partial(0, true, 0, false, 1, false);
	trigger_tower_0_1.stream_in.bind_by_iter(fe_stream_it_0_1);

	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_0_1_a = neighbour_dv_sig.begin_partial(2, false, 0, true, 0, false);
	sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_0_1_a = trigger_tower_0_1.neighbour_dv_in.begin_partial(0, false, 0, true);
	trigger_tower_0_1.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_0_1_a, neighbour_dv_sig_in_it_0_1_a);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_0_1_a = neighbour_dv_sig.begin_partial(2, false, 0, true, 1, false);
	sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_0_1_a = trigger_tower_0_1.neighbour_dv_out.begin_partial(0, false, 0, true);
	trigger_tower_0_1.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_0_1_a, neighbour_dv_sig_out_it_0_1_a);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_0_1_b = neighbour_dv_sig.begin_partial(0, false, 0, true, 1, false);
	sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_0_1_b = trigger_tower_0_1.neighbour_dv_in.begin_partial(1, false, 0, true);
	trigger_tower_0_1.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_0_1_b, neighbour_dv_sig_in_it_0_1_b);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_0_1_b = neighbour_dv_sig.begin_partial(0, false, 0, true, 0, false);
	sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_0_1_b = trigger_tower_0_1.neighbour_dv_out.begin_partial(1, false, 0, true);
	trigger_tower_0_1.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_0_1_b, neighbour_dv_sig_out_it_0_1_b);

	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_0_1_a = neighbour_stub_sig.begin_partial(2, false, 0, true, 0, false);
	sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_0_1_a = trigger_tower_0_1.neighbour_stub_in.begin_partial(0, false, 0, true);
	trigger_tower_0_1.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_0_1_a, neighbour_stub_sig_in_it_0_1_a);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_0_1_a = neighbour_stub_sig.begin_partial(2, false, 0, true, 1, false);
	sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_0_1_a = trigger_tower_0_1.neighbour_stub_out.begin_partial(0, false, 0, true);
	trigger_tower_0_1.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_0_1_a, neighbour_stub_sig_out_it_0_1_a);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_0_1_b = neighbour_stub_sig.begin_partial(0, false, 0, true, 1, false);
	sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_0_1_b = trigger_tower_0_1.neighbour_stub_in.begin_partial(1, false, 0, true);
	trigger_tower_0_1.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_0_1_b, neighbour_stub_sig_in_it_0_1_b);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_0_1_b = neighbour_stub_sig.begin_partial(0, false, 0, true, 0, false);
	sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_0_1_b = trigger_tower_0_1.neighbour_stub_out.begin_partial(1, false, 0, true);
	trigger_tower_0_1.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_0_1_b, neighbour_stub_sig_out_it_0_1_b);
	sc_map_square<sc_signal<bool> >::square_iterator result_write_en_it_0_1 = result_write_en.begin_partial(1, false, 0, true);
	trigger_tower_0_1.road_write_en.bind_by_iter(result_write_en_it_0_1);
	sc_map_square<sc_signal<track_finder::hit_stream> >::square_iterator result_road_it_0_1 = result_road.begin_partial(1, false, 0, true);
	trigger_tower_0_1.road_output.bind_by_iter(result_road_it_0_1);

// Trigger Tower 1-0
	trigger_tower_1_0.clk_LHC.bind(LHC_clock);
	trigger_tower_1_0.clk_x4.bind(LHCx4_clock);
	trigger_tower_1_0.clk_AM.bind(AM_clock);
	sc_map_cube<sc_signal<data_organizer::do_in_t > >::cube_iterator fe_stream_it_1_0 = fe_signals.begin_partial(0, true, 1, false, 0, false);
	trigger_tower_1_0.stream_in.bind_by_iter(fe_stream_it_1_0);

	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_1_0_a = neighbour_dv_sig.begin_partial(1, false, 0, true, 0, false);
	sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_1_0_a = trigger_tower_1_0.neighbour_dv_in.begin_partial(0, false, 0, true);
	trigger_tower_1_0.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_1_0_a, neighbour_dv_sig_in_it_1_0_a);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_1_0_a = neighbour_dv_sig.begin_partial(1, false, 0, true, 1, false);
	sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_1_0_a = trigger_tower_1_0.neighbour_dv_out.begin_partial(0, false, 0, true);
	trigger_tower_1_0.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_1_0_a, neighbour_dv_sig_out_it_1_0_a);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_1_0_b = neighbour_dv_sig.begin_partial(3, false, 0, true, 1, false);
	sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_1_0_b = trigger_tower_1_0.neighbour_dv_in.begin_partial(1, false, 0, true);
	trigger_tower_1_0.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_1_0_b, neighbour_dv_sig_in_it_1_0_b);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_1_0_b = neighbour_dv_sig.begin_partial(3, false, 0, true, 0, false);
	sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_1_0_b = trigger_tower_1_0.neighbour_dv_out.begin_partial(1, false, 0, true);
	trigger_tower_1_0.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_1_0_b, neighbour_dv_sig_out_it_1_0_b);

	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_1_0_a = neighbour_stub_sig.begin_partial(1, false, 0, true, 0, false);
	sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_1_0_a = trigger_tower_1_0.neighbour_stub_in.begin_partial(0, false, 0, true);
	trigger_tower_1_0.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_1_0_a, neighbour_stub_sig_in_it_1_0_a);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_1_0_a = neighbour_stub_sig.begin_partial(1, false, 0, true, 1, false);
	sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_1_0_a = trigger_tower_1_0.neighbour_stub_out.begin_partial(0, false, 0, true);
	trigger_tower_1_0.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_1_0_a, neighbour_stub_sig_out_it_1_0_a);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_1_0_b = neighbour_stub_sig.begin_partial(3, false, 0, true, 1, false);
	sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_1_0_b = trigger_tower_1_0.neighbour_stub_in.begin_partial(1, false, 0, true);
	trigger_tower_1_0.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_1_0_b, neighbour_stub_sig_in_it_1_0_b);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_1_0_b = neighbour_stub_sig.begin_partial(3, false, 0, true, 0, false);
	sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_1_0_b = trigger_tower_1_0.neighbour_stub_out.begin_partial(1, false, 0, true);
	trigger_tower_1_0.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_1_0_b, neighbour_stub_sig_out_it_1_0_b);
	sc_map_square<sc_signal<bool> >::square_iterator result_write_en_it_1_0 = result_write_en.begin_partial(2, false, 0, true);
	trigger_tower_1_0.road_write_en.bind_by_iter(result_write_en_it_1_0);
	sc_map_square<sc_signal<track_finder::hit_stream> >::square_iterator result_road_it_1_0 = result_road.begin_partial(2, false, 0, true);
	trigger_tower_1_0.road_output.bind_by_iter(result_road_it_1_0);


// Trigger Tower 1-1
	trigger_tower_1_1.clk_LHC.bind(LHC_clock);
	trigger_tower_1_1.clk_x4.bind(LHCx4_clock);
	trigger_tower_1_1.clk_AM.bind(AM_clock);
	sc_map_cube<sc_signal<data_organizer::do_in_t > >::cube_iterator fe_stream_it_1_1 = fe_signals.begin_partial(0, true, 1, false, 1, false);
	trigger_tower_1_1.stream_in.bind_by_iter(fe_stream_it_1_1);

	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_1_1_a = neighbour_dv_sig.begin_partial(3, false, 0, true, 0, false);
	sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_1_1_a = trigger_tower_1_1.neighbour_dv_in.begin_partial(0, false, 0, true);
	trigger_tower_1_1.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_1_1_a, neighbour_dv_sig_in_it_1_1_a);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_1_1_a = neighbour_dv_sig.begin_partial(3, false, 0, true, 1, false);
	sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_1_1_a = trigger_tower_1_1.neighbour_dv_out.begin_partial(0, false, 0, true);
	trigger_tower_1_1.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_1_1_a, neighbour_dv_sig_out_it_1_1_a);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_in_it_1_1_b = neighbour_dv_sig.begin_partial(2, false, 0, true, 1, false);
	sc_map_square<sc_in<bool> >::square_iterator neighbour_dv_in_it_1_1_b = trigger_tower_1_1.neighbour_dv_in.begin_partial(1, false, 0, true);
	trigger_tower_1_1.neighbour_dv_in.bind_by_iter(neighbour_dv_in_it_1_1_b, neighbour_dv_sig_in_it_1_1_b);
	sc_map_cube<sc_signal<bool> >::cube_iterator neighbour_dv_sig_out_it_1_1_b = neighbour_dv_sig.begin_partial(2, false, 0, true, 0, false);
	sc_map_square<sc_out<bool> >::square_iterator neighbour_dv_out_it_1_1_b = trigger_tower_1_1.neighbour_dv_out.begin_partial(1, false, 0, true);
	trigger_tower_1_1.neighbour_dv_out.bind_by_iter(neighbour_dv_out_it_1_1_b, neighbour_dv_sig_out_it_1_1_b);

	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_1_1_a = neighbour_stub_sig.begin_partial(3, false, 0, true, 0, false);
	sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_1_1_a = trigger_tower_1_1.neighbour_stub_in.begin_partial(0, false, 0, true);
	trigger_tower_1_1.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_1_1_a, neighbour_stub_sig_in_it_1_1_a);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_1_1_a = neighbour_stub_sig.begin_partial(3, false, 0, true, 1, false);
	sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_1_1_a = trigger_tower_1_1.neighbour_stub_out.begin_partial(0, false, 0, true);
	trigger_tower_1_1.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_1_1_a, neighbour_stub_sig_out_it_1_1_a);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_in_it_1_1_b = neighbour_stub_sig.begin_partial(2, false, 0, true, 1, false);
	sc_map_square<sc_in<do_stub_t> >::square_iterator neighbour_stub_in_it_1_1_b = trigger_tower_1_1.neighbour_stub_in.begin_partial(1, false, 0, true);
	trigger_tower_1_1.neighbour_stub_in.bind_by_iter(neighbour_stub_in_it_1_1_b, neighbour_stub_sig_in_it_1_1_b);
	sc_map_cube<sc_signal<do_stub_t> >::cube_iterator neighbour_stub_sig_out_it_1_1_b = neighbour_stub_sig.begin_partial(2, false, 0, true, 0, false);
	sc_map_square<sc_out<do_stub_t> >::square_iterator neighbour_stub_out_it_1_1_b = trigger_tower_1_1.neighbour_stub_out.begin_partial(1, false, 0, true);
	trigger_tower_1_1.neighbour_stub_out.bind_by_iter(neighbour_stub_out_it_1_1_b, neighbour_stub_sig_out_it_1_1_b);
	sc_map_square<sc_signal<bool> >::square_iterator result_write_en_it_1_1 = result_write_en.begin_partial(3, false, 0, true);
	trigger_tower_1_1.road_write_en.bind_by_iter(result_write_en_it_1_1);
	sc_map_square<sc_signal<track_finder::hit_stream> >::square_iterator result_road_it_1_1 = result_road.begin_partial(3, false, 0, true);
	trigger_tower_1_1.road_output.bind_by_iter(result_road_it_1_1);

//    roadAnalyzer.clk.bind(AM_clock);
//    roadAnalyzer.write_en.bind(result_write_en);
//    roadAnalyzer.hit_cnt.bind(hit_cnt_sig);
//    roadAnalyzer.road_in.bind(result_road);

#ifdef MTI_SYSTEMC
    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
    do_stub_out_sig.register_signal_modelsim<do_out_data>();
    fifo_stub_in.register_signal_modelsim<fm_out_data>();
#endif

    return;
}
