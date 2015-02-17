/*!
 * @file TT_TB_sim.cpp
 * @author Christian Amstutz
 * @date January 24, 2015
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

    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMboard.pattern_inputs, "AM_chip-0-0-0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[1].AMboard.pattern_inputs, "AM_chip-0-0-1");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[2].AMboard.pattern_inputs, "AM_chip-0-0-2");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[3].AMboard.pattern_inputs, "AM_chip-0-0-3");
    sc_trace(trace_file, testbench.trigger_tower_0_1.am_board_array[0].AMboard.pattern_inputs, "AM_chip-0-1-0");
    sc_trace(trace_file, testbench.trigger_tower_0_1.am_board_array[1].AMboard.pattern_inputs, "AM_chip-0-1-1");
    sc_trace(trace_file, testbench.trigger_tower_0_1.am_board_array[2].AMboard.pattern_inputs, "AM_chip-0-1-2");
    sc_trace(trace_file, testbench.trigger_tower_0_1.am_board_array[3].AMboard.pattern_inputs, "AM_chip-0-1-3");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[0].AMboard.pattern_inputs, "AM_chip-1-0-0");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[1].AMboard.pattern_inputs, "AM_chip-1-0-1");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[2].AMboard.pattern_inputs, "AM_chip-1-0-2");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[3].AMboard.pattern_inputs, "AM_chip-1-0-3");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[0].AMboard.pattern_inputs, "AM_chip-1-1-0");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[1].AMboard.pattern_inputs, "AM_chip-1-1-1");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[2].AMboard.pattern_inputs, "AM_chip-1-1-2");
    sc_trace(trace_file, testbench.trigger_tower_1_0.am_board_array[3].AMboard.pattern_inputs, "AM_chip-1-1-3");

    sc_trace(trace_file, testbench.trigger_tower_0_0.fifoManager.datapaths[0].buffer_write_en, "buffer_write_en");
    sc_trace(trace_file, testbench.trigger_tower_0_0.neighbour_dv_out, "neig_dv_out_0-0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.neighbour_stub_out, "neig_stub_out_0-0");
    sc_trace(trace_file, testbench.trigger_tower_0_1.neighbour_dv_in, "neig_dv_in_0-1");
    sc_trace(trace_file, testbench.trigger_tower_0_1.neighbour_stub_in, "neigh_stub_in_0-1");
    sc_trace(trace_file, testbench.trigger_tower_1_0.neighbour_dv_in, "neig_dv_in_1-0");
    sc_trace(trace_file, testbench.trigger_tower_1_0.neighbour_stub_in, "neigh_stub_in_1-0");
    sc_trace(trace_file, testbench.trigger_tower_1_1.neighbour_dv_in, "neig_dv_in_1-1");
    sc_trace(trace_file, testbench.trigger_tower_1_1.neighbour_stub_in, "neigh_stub_in_1-1");

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
