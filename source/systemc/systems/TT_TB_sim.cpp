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

    sc_trace(trace_file, testbench.trigger_tower_0_0.neighbour_dv_out, "neig_dv_out_0-0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.neighbour_stub_out, "neig_stub_out_0-0");
    sc_trace(trace_file, testbench.trigger_tower_0_1.neighbour_dv_in, "neig_dv_in_0-1");
    sc_trace(trace_file, testbench.trigger_tower_0_1.neighbour_stub_in, "neigh_stub_in_0-1");
    sc_trace(trace_file, testbench.trigger_tower_1_0.neighbour_dv_in, "neig_dv_in_1-0");
    sc_trace(trace_file, testbench.trigger_tower_1_0.neighbour_stub_in, "neigh_stub_in_1-0");
    sc_trace(trace_file, testbench.trigger_tower_1_1.neighbour_dv_in, "neig_dv_in_1-1");
    sc_trace(trace_file, testbench.trigger_tower_1_1.neighbour_stub_in, "neigh_stub_in_1-1");

    sc_trace(trace_file, testbench.trigger_tower_0_0.fifoManager.stub_in, "FM_stub_in");

    sc_trace(trace_file, testbench.trigger_tower_0_1.fifoManager.neighbour_dv_in, "FM_dv_in");
    sc_trace(trace_file, testbench.trigger_tower_0_1.fifoManager.datapaths[0].neighbour_dv_in, "DP_dv_in");

    sc_trace(trace_file, testbench.trigger_tower_0_1.fifoManager.dv_out, "dv_out");
    sc_trace(trace_file, testbench.trigger_tower_0_1.fifoManager.fifo_out, "fifo_out");



    //sc_trace(trace_file, testbench.dataOrganizer.stub_out, "DO_stub_out");

    //sc_trace(trace_file, testbench.sensor_modules_mpa.at(0,0,0).data_valid_signals, "dv_mpa0");
    //sc_trace(trace_file, testbench.sensor_modules_mpa.at(1,0,0).data_valid_signals, "dv_mpa1");
    //sc_trace(trace_file, testbench.sensor_modules_mpa.at(2,0,0).data_valid_signals, "dv_mpa2");
    //sc_trace(trace_file, testbench.sensor_modules_cbc.at(3,0,0).data_valid_signals, "dv_cbc3");
    //sc_trace(trace_file, testbench.sensor_modules_cbc.at(4,0,0).data_valid_signals, "dv_cbc4");
    //sc_trace(trace_file, testbench.sensor_modules_cbc.at(5,0,0).data_valid_signals, "dv_cbc5");
    //sc_trace(trace_file, testbench.fe_signals.at(0,0,0), "serial_link");

//    sc_trace(trace_file, testbench.fifo_stub_in, "fifo_stub_in");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.am_stub_outputs, "Patterns0");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[1].AMcontroller.am_stub_outputs, "Patterns1");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[2].AMcontroller.am_stub_outputs, "Patterns2");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[3].AMcontroller.am_stub_outputs, "Patterns3");


    // ----- Start simulation --------------------------------------------------

    #ifdef DEBUG
    std::cout << "Start simulation ..." << std::endl;
    #endif

    analyzer.register_simulation_start();
    sc_start(10000, SC_NS);
    analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    analyzer.print_report();
  
    return (0);
}
