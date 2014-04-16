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
        do_stubs(NR_DO_OUT_STUBS, "do_stubs"),
        fifo_not_empty(NR_DETECTOR_LAYERS, "fifo_not_empty", 1),
        fifo_write_en(NR_DETECTOR_LAYERS, "fifo_write_en", 1),
        fifo_stub_in(NR_DETECTOR_LAYERS, "fifo_stub_in", 1),
        fifo_read_en(NR_DETECTOR_LAYERS,  "fifo_read_en", 1),
        fifo_stub_out(NR_DETECTOR_LAYERS, "fifo_stub_out", 1),
        hitGenerator("Hit_Generator", "hits.txt"),
        sensor_modules(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor-module", 1, 1, 1),
        dataOrganizer("data_organizer",1, 1),
        stub_fifos(NR_DETECTOR_LAYERS, "stub_fifo", 1),
        amController("AM_controller"),
        amBoard("AM_board")
{
    true_sig.write(true);

    hitGenerator.hit_outputs.bind(hit_fifos);

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
    dataOrganizer.stub_out.bind(do_stubs);

    unsigned int id = 1;
    for(auto& single_stub_fifo : stub_fifos)
    {
        single_stub_fifo.clk(LHC_clock);
        single_stub_fifo.not_empty(fifo_not_empty[id]);
        single_stub_fifo.write_en(fifo_write_en[id]);
        single_stub_fifo.stub_in(fifo_stub_in[id]);
        single_stub_fifo.write_en(fifo_read_en[id]);
        single_stub_fifo.stub_out(fifo_stub_out[id]);

        ++id;
    }

    return;
}
