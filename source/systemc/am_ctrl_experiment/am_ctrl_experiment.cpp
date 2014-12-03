/*!
 * @file am_ctrl_experiment.cpp
 * @author Christian Amstutz
 * @date November 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <iostream>
#include <sstream>
#include <utility>

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_analyzer/sc_analyzer.hpp"

#include "am_ctrl_exp_config.hpp"
#include "am_ctrl_exp_top.hpp"

int sc_main(int argc, char *agv[])
{
    sc_analyzer analyzer;
    analyzer.register_model_setup_start();

    am_ctrl_exp_top testbench("AM_ctrl_experiment");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("am_ctrl_experiment");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.clock, "clock");
    sc_trace(trace_file, testbench.input_hit_sig[0], "input(0)");
    sc_trace(trace_file, testbench.input_hit_sig[1], "input(1)");

    sc_trace(trace_file, testbench.road_lookup.hit_inputs, "hit_inputs");
    sc_trace(trace_file, testbench.road_lookup.process_roads_sig, "process_roads_sig");
    sc_trace(trace_file, testbench.road_lookup.roads_detected, "roads_detected");
    sc_trace(trace_file, testbench.road_lookup.read_controller.current_state, "read_state");
    sc_trace(trace_file, testbench.road_lookup.write_controller.current_state, "write_state");
    sc_trace(trace_file, testbench.road_lookup.road_output, "road_output");

    sc_trace(trace_file, testbench.pattern_mem_addr_sig, "pattern_mem_in");
    sc_trace(trace_file, testbench.pattern_mem_out_sig, "pattern_mem_out");

    sc_trace(trace_file, testbench.hit_search_sig, "hit_search");
    sc_trace(trace_file, testbench.hit_buffer.superstrip_search, "superstrip_search");
    sc_trace(trace_file, testbench.hit_buffer.pure_superstrips, "pure_superstrips");
    sc_trace(trace_file, testbench.hit_buffer.write_controller.current_state, "hit_buf_write_state");
    sc_trace(trace_file, testbench.hit_buffer.lookup_controller.current_state, "lookup_state");
    sc_trace(trace_file, testbench.hit_buffer.output_controller.current_state, "output_state");
    sc_trace(trace_file, testbench.hit_buffer.transmit_event_begin, "transmit_event_begin");
    sc_trace(trace_file, testbench.hit_buffer.hit_outputs, "hitbuffer.hit_outputs");

    sc_trace(trace_file, testbench.road_proc.road_input, "road_input");
    sc_trace(trace_file, testbench.road_proc.road_lookup, "road_lookup");
    sc_trace(trace_file, testbench.road_proc.found_pattern, "found_pattern");
    sc_trace(trace_file, testbench.road_proc.superstrip_lookup, "superstrip_lookup");

    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << std::endl;
    std::cout << "Start simulation ..." << std::endl;

    analyzer.register_simulation_start();
    sc_start(1000, SC_NS);
    analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    std::cout << "Simulation ended." << std::endl;

    analyzer.print_report();
  
    return (0);
}
