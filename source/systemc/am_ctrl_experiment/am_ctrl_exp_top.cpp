/*!
 * @file am_ctrl_exp_top.cpp
 * @author Christian Amstutz
 * @date Nov 14, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_ctrl_exp_top.hpp"

#ifdef MTI_SYSTEMC
SC_MODULE_EXPORT(am_ctrl_exp_top);
#endif

// *****************************************************************************

am_ctrl_exp_top::am_ctrl_exp_top(const sc_module_name _name) :
        sc_module(_name),
        clock("clock", CLOCK_PERIOD_NS, SC_NS, 0.5, 10, SC_NS, true),
        input_hit_sig(LAYER_NUMBER, "input_hit_sig"),
        hit_buffer_ss_store_sig(LAYER_NUMBER, "hit_buffer_ss_subs_sig"),
        hit_buffer_subs_store_sig(LAYER_NUMBER, "hit_buffer_store_subs_sig"),
        am_input_sig(LAYER_NUMBER, "am_input_sig"),
        am_output_sig("am_output_sig"),
        pattern_mem_addr_sig("pattern_mem_addr_sig"),
        pattern_mem_out_sig(LAYER_NUMBER, "pattern_mem_out_sig"),
        hit_search_sig(LAYER_NUMBER, "hit_search_sig"),
        hit_result_sig(LAYER_NUMBER, "hit_result_sig"),
        output_hit_sig(LAYER_NUMBER, "output_hit_sig"),
        hit_proc("hit_processor"),
        hit_buffer("hit_buffer"),
        road_lookup("road_lookup"),
        pattern_lookup("pattern_lookup"),
        road_proc("road_processor")
{
    hit_proc.clk.bind(clock);
    hit_proc.hit_input.bind(input_hit_sig);
    hit_proc.am_superstrip_out.bind(am_input_sig);
    hit_proc.hitbuf_superstrip_out.bind(hit_buffer_ss_store_sig);
    hit_proc.hitbuf_substrip_out.bind(hit_buffer_subs_store_sig);

    hit_buffer.clk.bind(clock);
    hit_buffer.superstrip_inputs.bind(hit_buffer_ss_store_sig);
    hit_buffer.substrip_inputs.bind(hit_buffer_subs_store_sig);
    hit_buffer.superstrip_search.bind(hit_search_sig);
    hit_buffer.hit_outputs.bind(hit_result_sig);

    road_lookup.clk.bind(clock);
    road_lookup.hit_inputs.bind(am_input_sig);
    road_lookup.road_output.bind(am_output_sig);

    pattern_lookup.clk.bind(clock);
    pattern_lookup.road_input.bind(pattern_mem_addr_sig);
    pattern_lookup.superstrip_outputs.bind(pattern_mem_out_sig);

    road_proc.clk.bind(clock);
    road_proc.road_input.bind(am_output_sig);
    road_proc.road_lookup.bind(pattern_mem_addr_sig);
    road_proc.found_pattern.bind(pattern_mem_out_sig);
    road_proc.superstrip_lookup.bind(hit_search_sig);
    road_proc.hit_lookup_result.bind(hit_result_sig);
    road_proc.hit_output.bind(output_hit_sig);

    SC_THREAD(generate_input);

//#ifdef MTI_SYSTEMC
//    hit_fifos.register_signal_modelsim<hit_generator::hitgen_stub_t>();
//    do_stub_out_sig.register_signal_modelsim<do_out_data>();
//    fifo_stub_in.register_signal_modelsim<fm_out_data>();
//#endif

    return;
}

// *****************************************************************************
void am_ctrl_exp_top::generate_input()
{
    input_hit_sig[0].write(IDLE_EVENT);
    wait(50, SC_NS);
    input_hit_sig[0].write(START_EVENT);
    input_hit_sig[1].write(START_EVENT);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x11);
    input_hit_sig[1].write(0x11);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x12);
    input_hit_sig[1].write(0x12);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x08);
    input_hit_sig[1].write(0x09);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x3);
    input_hit_sig[1].write(IDLE_EVENT);
    wait(10, SC_NS);
    input_hit_sig[0].write(IDLE_EVENT);
    wait(80, SC_NS);
    input_hit_sig[0].write(START_EVENT);
    input_hit_sig[1].write(START_EVENT);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x9);
    input_hit_sig[1].write(0x8);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x3);
    input_hit_sig[1].write(IDLE_EVENT);
    wait(10, SC_NS);
    input_hit_sig[0].write(IDLE_EVENT);
    wait(100, SC_NS);
    hit_search_sig[0].write(START_EVENT);
    hit_search_sig[1].write(START_EVENT);
    wait(10,SC_NS);
    hit_search_sig[0].write(0x02);
    hit_search_sig[1].write(0x02);
    wait(10, SC_NS);
    hit_search_sig[0].write(IDLE_EVENT);
    hit_search_sig[1].write(IDLE_EVENT);
    wait(100, SC_NS);
    pattern_mem_addr_sig.write(1);
    wait(10, SC_NS);
    pattern_mem_addr_sig.write(3);


    return;
}
