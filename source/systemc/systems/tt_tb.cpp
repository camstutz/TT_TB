/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date June 4, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
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
        true_sig("TRUE"),
        hit_fifos_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo", 0, 0, 0, 0),
        hit_fifos_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo", NR_DETECTOR_MPA_LAYERS, 0, 0, 0),
        fe_signals(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "fe_signals"),
        do_stub_out_sig(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "do_stub_out_sig"),
        fifo_stub_in(NR_AM_BOARDS, NR_DETECTOR_LAYERS, "fifo_stub_in"),
        result_write_en(NR_AM_BOARDS, "result_write_en"),
        result_road(NR_AM_BOARDS, "result_road"),
        hit_cnt_sig("hit_cnt_sig"),
        hitGenerator("Hit_Generator", "data/hits.txt"),
        sensor_modules_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor_module", 0, 0, 0),
        sensor_modules_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor_module", NR_DETECTOR_MPA_LAYERS, 0, 0),
        dataOrganizer("data_organizer", 0, 0),
        fifoManager("FIFO_manager"),
        am_lane_array(NR_AM_BOARDS, "am_lane"),
        roadAnalyzer("road_analyzer")
{
    true_sig.write(true);

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

    dataOrganizer.clk.bind(LHC_clock);
    dataOrganizer.rst.bind(true_sig);
    sc_map_cube<sc_signal<sc_bv<DC_OUTPUT_WIDTH> > >::iterator fe_it = fe_signals.begin();
    dataOrganizer.stream_in.bind_by_iter(fe_it);
    dataOrganizer.stub_out.bind(do_stub_out_sig);

    fifoManager.clk.bind(LHCx4_clock);
    fifoManager.rst.bind(true_sig);
    fifoManager.stub_in.bind(do_stub_out_sig);
    fifoManager.fifo_out.bind(fifo_stub_in);

    unsigned int lane_nr = 0;
    sc_map_linear<am_lane>::iterator am_lane_it = am_lane_array.begin();
    for(; am_lane_it != am_lane_array.end(); ++am_lane_it)
    {
        am_lane_it->clk.bind(AM_clock);
        am_lane_it->rst.bind(true_sig);
        sc_map_square<sc_signal<fm_out_data> >::square_iterator fifo_stub_it = fifo_stub_in.begin_partial(lane_nr, false, 0, true);
        am_lane_it->fifo_inputs.bind_by_iter(fifo_stub_it);
        am_lane_it->road_write_en.bind(result_write_en[lane_nr]);
        am_lane_it->road_output.bind(result_road[lane_nr]);

        ++lane_nr;
    }

    roadAnalyzer.clk.bind(AM_clock);
    roadAnalyzer.write_en.bind(result_write_en);
    roadAnalyzer.hit_cnt.bind(hit_cnt_sig);
    roadAnalyzer.road_in.bind(result_road);

#ifdef MTI_SYSTEMC
    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
    do_stub_out_sig.register_signal_modelsim<do_out_data>();
    fifo_stub_in.register_signal_modelsim<fm_out_data>();
#endif

    return;
}
