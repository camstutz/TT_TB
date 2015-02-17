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

    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].stub_fifo_array[0].not_empty, "not_empty");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].stub_fifo_array[0].stub_out, "stub_out");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].stub_fifo_array[0].stub_in, "stub_in");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].stub_fifo_array[0].write_en, "write_en");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].stub_fifo_array[0].read_en, "read_en");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.fifo_controller_array[0].FSM.event_active, "event_active-FIFOCONTROLLER");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.read_controller.event_active, "event_active-READCONTROLLER");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.stub_outputs, "T0_B0_stub_out");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.fifo_controller_array[0].FSM.is_timestamp, "FIFO_FSM_is_timestamp");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.fifo_controller_array[0].FSM.event_start, "FIFO_FSM_event_start");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.fifo_controller_array[0].FSM.current_state, "FIFO_FSM_current_state");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.read_controller.current_state, "read_controller.current_state");
    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[0].AMcontroller.read_controller.layers_active, "read_controller.layers_active");
//    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[1].AMcontroller.stub_outputs, "T0_B1_stub_out");
//    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[2].AMcontroller.stub_outputs, "T0_B2_stub_out");
//    sc_trace(trace_file, testbench.trigger_tower_0_0.am_board_array[3].AMcontroller.stub_outputs, "T0_B3_stub_out");

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
