/*!
 * @file tracak_finder.cpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "track_finder.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(track_finder);
#endif

// *****************************************************************************

track_finder::track_finder(const sc_module_name _name,
        const track_finder_config configuration) :
        sc_module(_name),
        layer_nr(configuration.layer_nr),
        clk("clk"),
        hit_input(layer_nr, "hit_input"),
        hit_output(layer_nr, "hit_output"),
        hit_buffer_ss_store_sig(layer_nr, "hit_buffer_ss_subs_sig"),
        hit_buffer_subs_store_sig(layer_nr, "hit_buffer_store_subs_sig"),
        am_input_sig(layer_nr, "am_input_sig"),
        am_output_sig("am_output_sig"),
        pattern_mem_addr_sig("pattern_mem_addr_sig"),
        pattern_mem_out_sig(layer_nr, "pattern_mem_out_sig"),
        hit_search_sig(layer_nr, "hit_search_sig"),
        hit_result_sig(layer_nr, "hit_result_sig"),
        patterns(layer_nr),
        hit_proc("hit_processor"),
        temp_hit_buffer("temp_hit_buffer"),
        road_lookup("road_lookup", &patterns),
        pattern_lookup("pattern_lookup", &patterns),
        road_proc("road_processor")
{
    //patterns.import_text_file("patternbank.txt");
    patterns.generate_patterns_straight(10000);

    hit_proc.clk.bind(clk);
    hit_proc.hit_input.bind(hit_input);
    hit_proc.am_superstrip_out.bind(am_input_sig);
    hit_proc.hitbuf_superstrip_out.bind(hit_buffer_ss_store_sig);
    hit_proc.hitbuf_substrip_out.bind(hit_buffer_subs_store_sig);

    temp_hit_buffer.clk.bind(clk);
    temp_hit_buffer.superstrip_inputs.bind(hit_buffer_ss_store_sig);
    temp_hit_buffer.substrip_inputs.bind(hit_buffer_subs_store_sig);
    temp_hit_buffer.superstrip_search.bind(hit_search_sig);
    temp_hit_buffer.hit_outputs.bind(hit_result_sig);

    road_lookup.clk.bind(clk);
    road_lookup.hit_inputs.bind(am_input_sig);
    road_lookup.road_output.bind(am_output_sig);

    pattern_lookup.clk.bind(clk);
    pattern_lookup.road_input.bind(pattern_mem_addr_sig);
    pattern_lookup.superstrip_outputs.bind(pattern_mem_out_sig);

    road_proc.clk.bind(clk);
    road_proc.road_input.bind(am_output_sig);
    road_proc.road_lookup.bind(pattern_mem_addr_sig);
    road_proc.found_pattern.bind(pattern_mem_out_sig);
    road_proc.superstrip_lookup.bind(hit_search_sig);
    road_proc.hit_lookup_result.bind(hit_result_sig);
    road_proc.hit_output.bind(hit_output);

    return;
}
