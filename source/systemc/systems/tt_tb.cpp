/*!
 * @file tt_tb.cpp
 * @author Christian Amstutz
 * @date August 3, 2015
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

tt_tb::tt_tb(const sc_module_name _name, const track_trigger_config configuration) :
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        true_sig("true_sig"),
        hit_fifos(configuration.get_chip_addresses(), "hit_fifo"),
        gbt_links(configuration.get_module_addresses(), "GBT_link"),
        dtc_links(NR_PRB_PER_TRIGGER_TOWER, "DTC_link"),
        result_hits(NR_PRB_PER_TRIGGER_TOWER * NR_AM_BOARDS, NR_DETECTOR_LAYERS, "result_road"),
        hit_cnt_sig("hit_cnt_sig"),
        hitGenerator("Hit_Generator", configuration.hit_generator),
        sensor_modules(configuration.get_module_addresses(), "sensor_module", configuration.sensor_modules),
        DTCs(1, "DTC", configuration.dtcs),
        trigger_tower_0("trigger_tower", configuration.trigger_tower),
        roadAnalyzer("road_analyzer")
{
    hitGenerator.stub_outputs.bind(hit_fifos);
    hitGenerator.hit_cnt(hit_cnt_sig);

    for( sc_map_list<sensor_module_address, sensor_module>::iterator module_it = sensor_modules.begin();
         module_it != sensor_modules.end();
         ++module_it)
    {
        module_it->clk.bind(LHC_clock);
        std::vector<chip_address> chip_addresses = module_it->configuration.address.get_chips(*(module_it->configuration.type) );
        sc_map_list_range<chip_address> module_chips(chip_addresses);
        module_it->stub_inputs.bind(hit_fifos(module_chips));
        module_it->gbt_link.bind(gbt_links[module_it->configuration.address]);
    }

    unsigned int dtc_id = 0;
    for ( sc_map_linear<dtc>::iterator dtc_it = DTCs.begin();
          dtc_it != DTCs.end();
          ++dtc_it)
    {
        dtc_it->clk.bind(LHC_clock);
        sc_map_list_range<sensor_module_address> module_list(dtc_it->configuration.sensor_modules);
        dtc_it->gbt_inputs.bind(gbt_links(module_list));
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
