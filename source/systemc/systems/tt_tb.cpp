/*!
 * @file tt_tb.cpp
 * @author Christian Amstutz
 * @date August 27, 2015
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
        LHC_clock("LHC_clock", configuration.LHC_clock_period, SC_NS, 0.5, 25, SC_NS, true),
        true_sig("true_sig"),
        hit_fifos(configuration.get_chip_addresses(), "hit_fifo", configuration.hit_FIFO_size),
        gbt_links(configuration.get_module_addresses(), "GBT_link"),
        dtc_links(configuration.trigger_tower.prb_nr, "DTC_link"),
        result_hits(configuration.trigger_tower.prb_nr * configuration.trigger_tower.AM_boards_per_prb, configuration.trigger_tower.layer_nr, "result_road"),
        hit_cnt_sig("hit_cnt_sig"),
        hitGenerator("Hit_Generator", configuration.hit_generator),
        sensor_modules(configuration.get_module_addresses(), "sensor_module", configuration.sensor_modules),
        DTCs(configuration.dtcs.size(), "DTC", configuration.dtcs),
        trigger_tower_0("trigger_tower", configuration.trigger_tower),
        roadAnalyzer("road_analyzer", configuration.road_analyzer)
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
    trigger_tower_0.dtc_inputs.bind(dtc_links);
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
