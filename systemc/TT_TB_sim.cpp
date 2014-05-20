/*!
 * @file TT_TB_sim.cpp
 * @author Christian Amstutz
 * @date Mar 13, 2014
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

#include "../lib/systemc_helpers/sc_analyzer/sc_analyzer.hpp"

#include "tt_tb.hpp"
//#include "TT_configuration.hpp"

int sc_main(int argc, char *agv[])
{
    sc_analyzer analyzer;
    //analyzer.register_model_setup_start();

    tt_tb testbench("TT_TB");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.LHC_clock, "LHC_clock");
    sc_trace(trace_file, testbench.LHCx4_clock, "LHCx4_clock");
    sc_trace(trace_file, testbench.AM_clock, "AM_clock");
    sc_trace(trace_file, testbench.dataOrganizer.stub_out, "DO_stub_out");

    sc_trace(trace_file, testbench.fe_signals, "serial_link");

    sc_trace(trace_file, testbench.fifo_stub_in, "fifo_stub_in");
    sc_trace(trace_file, testbench.am_lane_array[0].fifo_stub_out_sig[0], "fifo_stub_out_sig_0-0");
    sc_trace(trace_file, testbench.am_lane_array[1].fifo_stub_out_sig[0], "fifo_stub_out_sig_1-0");
    sc_trace(trace_file, testbench.am_lane_array[2].fifo_stub_out_sig[0], "fifo_stub_out_sig_2-0");
    sc_trace(trace_file, testbench.am_lane_array[3].fifo_stub_out_sig[0], "fifo_stub_out_sig_3-0");
    sc_trace(trace_file, testbench.am_lane_array[1].init_ev_sig, "init_ev_sig");
    sc_trace(trace_file, testbench.am_lane_array[1].am_write_en_sig, "am_write_en_sig");
    sc_trace(trace_file, testbench.am_lane_array[1].AMboard.fsm.current_state, "AM_board.current_state");
    sc_trace(trace_file, testbench.am_lane_array[0].am_pattern_sig, "am_pattern");
    sc_trace(trace_file, testbench.am_lane_array[1].am_pattern_sig, "am_pattern");
    sc_trace(trace_file, testbench.am_lane_array[2].am_pattern_sig, "am_pattern");
    sc_trace(trace_file, testbench.am_lane_array[3].am_pattern_sig, "am_pattern");
    sc_trace(trace_file, testbench.am_lane_array[0].am_road_sig, "am_road_0");
    sc_trace(trace_file, testbench.am_lane_array[1].am_road_sig, "am_road_1");
    sc_trace(trace_file, testbench.am_lane_array[2].am_road_sig, "am_road_2");
    sc_trace(trace_file, testbench.am_lane_array[3].am_road_sig, "am_road_3");
    sc_trace(trace_file, testbench.am_lane_array[0].road_output, "road_out_0");
    sc_trace(trace_file, testbench.am_lane_array[1].road_output, "road_out_1");
    sc_trace(trace_file, testbench.am_lane_array[2].road_output, "road_out_2");
    sc_trace(trace_file, testbench.am_lane_array[3].road_output, "road_out_3");


    // ----- Start simulation --------------------------------------------------

    #ifdef DEBUG
    std::cout << "Start simulation ..." << std::endl;
    #endif

    //analyzer.register_simulation_start();
    sc_start(50000, SC_NS);
    //analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    //analyzer.print_report();
  
    return (0);
}
