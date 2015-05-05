/*!
 * @file tt_tb.cpp
 * @author Christian Amstutz
 * @date May 5, 2015
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
        true_sig("true_sig"),
        hit_fifos_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo_mpa", 0, 0, 0, 0),
        hit_fifos_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_fifo_cbc", NR_DETECTOR_MPA_LAYERS, 0, 0, 0),
        gbt_links(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "GBT_link"),
        dtc_links(NR_PRB_PER_TRIGGER_TOWER, "DTC_link"),
        result_hits(NR_PRB_PER_TRIGGER_TOWER * NR_AM_BOARDS, NR_DETECTOR_LAYERS, "result_road"),
        hit_cnt_sig("hit_cnt_sig"),
        hitGenerator("Hit_Generator", "data/hits.txt"),
        sensor_modules_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor_module_mpa", 0, 0, 0),
        sensor_modules_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, "sensor_module_cbc", NR_DETECTOR_MPA_LAYERS, 0, 0),
        DTCs(NR_PRB_PER_TRIGGER_TOWER, "DTC"),
        trigger_tower_0("trigger_tower"),
        roadAnalyzer("road_analyzer")
{
    hitGenerator.mpa_stub_outputs.bind(hit_fifos_mpa);
    hitGenerator.cbc_stub_outputs.bind(hit_fifos_cbc);
    hitGenerator.hit_cnt(hit_cnt_sig);

    sc_map_cube<sensor_module_MPA>::iterator mpa_module_it = sensor_modules_mpa.begin();
    for (; mpa_module_it != sensor_modules_mpa.end(); ++mpa_module_it)
    {
        sc_map_cube<sensor_module_MPA>::full_key_type module_key = sensor_modules_mpa.get_key(*mpa_module_it).second;
        mpa_module_it->clk.bind(LHC_clock);
        mpa_module_it->stub_inputs.bind(hit_fifos_mpa(module_key.Z_dim, module_key.Z_dim,
                module_key.Y_dim, module_key.Y_dim,
                module_key.X_dim, module_key.X_dim,
                0, sc_map::max));
        mpa_module_it->gbt_link.bind(gbt_links.at(module_key.Z_dim, module_key.Y_dim, module_key.X_dim));
    }

    sc_map_cube<sensor_module_CBC>::iterator cbc_module_it = sensor_modules_cbc.begin();
    for (; cbc_module_it != sensor_modules_cbc.end(); ++cbc_module_it)
    {
        sc_map_cube<sensor_module_CBC>::full_key_type module_key = sensor_modules_cbc.get_key(*cbc_module_it).second;
        cbc_module_it->clk.bind(LHC_clock);
        cbc_module_it->stub_inputs.bind(hit_fifos_cbc(module_key.Z_dim, module_key.Z_dim,
                module_key.Y_dim, module_key.Y_dim,
                module_key.X_dim, module_key.X_dim,
                0, sc_map::max));
        cbc_module_it->gbt_link.bind(gbt_links.at(module_key.Z_dim, module_key.Y_dim, module_key.X_dim));
    }

    unsigned int dtc_id = 0;
    sc_map_linear<dtc>::iterator dtc_it = DTCs.begin();
    for (; dtc_it != DTCs.end(); ++dtc_it)
    {
        dtc_it->clk.bind(LHC_clock);
        dtc_it->gbt_inputs.bind(gbt_links(3*dtc_id, 3*dtc_id+2, 0, 0, 0, 0));

        dtc_it->tower_output.bind(dtc_links[dtc_id]);

        ++dtc_id;
    }

    trigger_tower_0.clk.bind(LHC_clock);
    trigger_tower_0.dtc_inputs.at(0,0).bind(dtc_links[0]);
    trigger_tower_0.dtc_inputs.at(1,0).bind(dtc_links[1]);
    trigger_tower_0.hit_outputs.bind(result_hits);

    roadAnalyzer.hit_cnt.bind(hit_cnt_sig);
    roadAnalyzer.filtered_hits.bind(result_hits);

#ifdef MTI_SYSTEMC
    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
    do_stub_out_sig.register_signal_modelsim<do_out_data>();
    fifo_stub_in.register_signal_modelsim<fm_out_data>();
#endif

    return;
}
