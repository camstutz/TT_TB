/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "tt_tb.hpp"

// *****************************************************************************

/*!
 * @class sensor_module
 *
 */

tt_tb::tt_tb(const sc_module_name _name) :
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        true_sig("TRUE"),
        hit_fifos(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo", 1, 1, 1, 1),
        fe_signals(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "fe_signals", 1, 1, 1),
        fifo_not_empty(NR_DETECTOR_LAYERS, "fifo_not_empty", 1),
        fifo_stub_in(NR_DETECTOR_LAYERS, "fifo_stub_in", 1),
        fifo_read_en(NR_DETECTOR_LAYERS,  "fifo_read_en", 1),
        fifo_stub_out(NR_DETECTOR_LAYERS, "fifo_stub_out", 1),
        am_init_ev("init_ev"),
        am_write_en(NR_DETECTOR_LAYERS, "am_write_en", 1),
        am_stubs_in(NR_DETECTOR_LAYERS, "am_stubs_in", 1),
        am_data_ready("am_data_ready"),
        am_road("am_road"),
        result_write_en("result_write_en"),
        result_road("result_road"),
        hit_cnt_sig("hit_cnt_sig"),
        hitGenerator("Hit_Generator", "hits.txt"),
        sensor_modules(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor-module", 1, 1, 1),
        dataOrganizer("data_organizer",1, 1),
        stub_fifos(NR_DETECTOR_LAYERS, "stub_fifo", 1),
        amController("AM_controller"),
        amBoard("AM_board"),
        roadAnalyzer("road_analyzer")
{
    true_sig.write(true);

    hitGenerator.hit_outputs.bind(hit_fifos);
    hitGenerator.hit_cnt(hit_cnt_sig);

    for (auto& sens_module : sensor_modules)
    {
        auto full_key = sensor_modules.get_key(sens_module);

        sens_module.clk(LHC_clock);
        auto fifo_it  = hit_fifos.begin_partial(full_key.second.Z_dim, false, full_key.second.Y_dim, false, full_key.second.X_dim, false, 0, true);
        sens_module.stub_inputs.bind_by_iter(fifo_it);
        sens_module.dc_out.bind(fe_signals.at(full_key.second.Z_dim, full_key.second.Y_dim, full_key.second.X_dim));
    }

    dataOrganizer.clk(LHC_clock);
    dataOrganizer.rst(true_sig);
    auto fe_it = fe_signals.begin();
    dataOrganizer.stream_in.bind_by_iter(fe_it);
    dataOrganizer.stub_out.bind(fifo_stub_in);

    unsigned int id = 1;
    for(auto& single_stub_fifo : stub_fifos)
    {
        single_stub_fifo.clk.bind(LHC_clock);
        single_stub_fifo.rst(true_sig);
        single_stub_fifo.not_empty.bind(fifo_not_empty[id]);
        single_stub_fifo.stub_in.bind(fifo_stub_in[id]);
        single_stub_fifo.read_en.bind(fifo_read_en[id]);
        single_stub_fifo.stub_out.bind(fifo_stub_out[id]);

        ++id;
    }

    amController.clk.bind(LHC_clock);
    amController.init.bind(true_sig);
    amController.fifo_not_empty.bind(fifo_not_empty);
    amController.fifo_read_en.bind(fifo_read_en);
    amController.stub_inputs.bind(fifo_stub_out);
    amController.init_ev.bind(am_init_ev);
    amController.am_write_en.bind(am_write_en);
    amController.am_stub_outputs.bind(am_stubs_in);
    amController.data_ready.bind(am_data_ready);
    amController.road_in.bind(am_road);
    amController.road_write_en.bind(result_write_en);
    amController.road_output.bind(result_road);

    amBoard.clk.bind(LHC_clock);
    amBoard.rst.bind(true_sig);
    amBoard.init_ev.bind(am_init_ev);
    amBoard.write_en.bind(am_write_en);
    amBoard.pattern_inputs.bind(am_stubs_in);
    amBoard.data_ready.bind(am_data_ready);
    amBoard.road_output.bind(am_road);

    roadAnalyzer.clk(LHC_clock);
    roadAnalyzer.write_en(result_write_en);
    roadAnalyzer.hit_cnt(hit_cnt_sig);
    roadAnalyzer.road_in(result_road);

    return;
}
