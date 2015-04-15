/*!
 * @file TT_TB_sim.cpp
 * @author Christian Amstutz
 * @date February 17, 2015

 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include <iostream>
#include <sstream>
#include <utility>

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_analyzer/sc_analyzer.hpp"

#include "tt_tb.hpp"

int sc_main(int argc, char *agv[])
{
    sc_analyzer analyzer;
    analyzer.register_model_setup_start();

    tt_tb testbench("TT_TB");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.LHC_clock, "LHC_clock");
    sc_trace(trace_file, testbench.LHCx4_clock, "LHCx4_clock");
    sc_trace(trace_file, testbench.AM_clock, "AM_clock");

    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].TrackFinder.road_proc.road_input, "road_in0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].TrackFinder.road_proc.command_buffer_write_sig, "write_sig0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].TrackFinder.road_proc.command_buffer_delayed_sig, "delayed_sig0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].TrackFinder.road_proc.found_pattern, "found_pattern0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].TrackFinder.road_proc.superstrip_lookup, "superstrip_lookup0");
    //sc_trace(trace_file, testbench.trigger_tower_0_0.road_output, "out0");

    // ----- Start simulation --------------------------------------------------

    #ifdef DEBUG
    std::cout << "Start simulation ..." << std::endl;
    #endif

    analyzer.register_simulation_start();
    sc_start(3000, SC_NS);
    analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    analyzer.print_report();
  
    return (0);
}
