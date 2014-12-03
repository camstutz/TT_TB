/*!
 * @file am_ctrl_exp_top.cpp
 * @author Christian Amstutz
 * @date December 3, 2014
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

const std::string am_ctrl_exp_top::in_filename = "ss.txt";
const std::string am_ctrl_exp_top::out_filename = "ss_out.txt";

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
    SC_THREAD(log_input);
        input_hit_sig.make_sensitive(sensitive);
    SC_THREAD(log_result);
        hit_result_sig.make_sensitive(sensitive);

    return;
}

// *****************************************************************************
am_ctrl_exp_top::~am_ctrl_exp_top()
{
    std::cout << in_log_buffer.str();
    std::cout << out_log_buffer.str();

    return;
}

// *****************************************************************************
void am_ctrl_exp_top::generate_input()
{
    input_hit_sig[0].write(hit_stream::IDLE);
    input_hit_sig[1].write(hit_stream::IDLE);
    wait(50, SC_NS);
    input_hit_sig[0].write(hit_stream::START_WORD);
    input_hit_sig[1].write(hit_stream::START_WORD);
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
    input_hit_sig[1].write(hit_stream::IDLE);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x1F);
    input_hit_sig[1].write(hit_stream::IDLE);
    wait(10, SC_NS);
    input_hit_sig[0].write(hit_stream::IDLE);
    wait(80, SC_NS);
    input_hit_sig[0].write(hit_stream::START_WORD);
    input_hit_sig[1].write(hit_stream::START_WORD);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x9);
    input_hit_sig[1].write(0x8);
    wait(10, SC_NS);
    input_hit_sig[0].write(0x3);
    input_hit_sig[1].write(hit_stream::IDLE);
    wait(10, SC_NS);
    input_hit_sig[0].write(hit_stream::IDLE);
    wait(100, SC_NS);

    return;
}

// *****************************************************************************
void am_ctrl_exp_top::log_input()
{
    in_log_buffer << std::endl
                  << "Simulation Input of AM experiment:" << std::endl
                  << "**********************************" << std::endl;

    while(1)
    {
        wait();

        in_log_buffer << sc_time_stamp() << ": ";
        for(unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            in_log_buffer << std::hex << input_hit_sig[layer].read() << ", ";
        }
        in_log_buffer << std::endl;
    }
}

// *****************************************************************************
void am_ctrl_exp_top::log_result()
{
    out_log_buffer << std::endl
                   << "Simulation Output of AM experiment:" << std::endl
                   << "***********************************" << std::endl;

    while(1)
    {
        wait();

        out_log_buffer << sc_time_stamp() << ": ";
        for(unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
        {
            out_log_buffer << std::hex << hit_result_sig[layer].read() << ", ";
        }
        out_log_buffer << std::endl;
    }
}
