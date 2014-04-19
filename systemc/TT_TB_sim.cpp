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
    analyzer.register_model_setup_start();

    tt_tb testbench("TT_TB");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.LHC_clock, "LHC_clk");
    sc_trace(trace_file, testbench.dataOrganizer.stub_out, "DO_stub_out");

    sc_trace(trace_file, testbench.fe_signals, "serial_link");

    sc_trace(trace_file, testbench.amController.fifo_not_empty, "FIFO_not_empty");
    sc_trace(trace_file, testbench.amController.stub_inputs[0], "AM_stub_in_0");
    sc_trace(trace_file, testbench.amController.am_write_en[0], "AM_write_en_0");
    sc_trace(trace_file, testbench.amController.am_stub_outputs[0], "AM_stub_out_0");
    sc_trace(trace_file, testbench.amController.main_am_fsm.current_state,"AM_current_state");
    sc_trace(trace_file, testbench.amController.hit_controller.hit_controllers[0].stub_read,"stub_read_0");
    sc_trace(trace_file, testbench.amController.hee_reg_sig[0],"hee_reg_sig_0");
    sc_trace(trace_file, testbench.amController.hit_controller.new_hit[0],"new_hit_0");
    sc_trace(trace_file, testbench.amController.main_am_fsm.pop[0],"pop_0");
    sc_trace(trace_file, testbench.amController.main_am_fsm.finish_road,"finish_road");
    sc_trace(trace_file, testbench.amController.fifo_fsm_array[0].current_state, "FIFO_current_state");

    sc_trace(trace_file, testbench.amController.data_ready, "road_data_ready");
    sc_trace(trace_file, testbench.amController.road_in, "road_in");
    sc_trace(trace_file, testbench.amController.road_write_en, "road_write_en");
    sc_trace(trace_file, testbench.amController.road_output, "road_output");


    // ----- Start simulation --------------------------------------------------

    #ifdef DEBUG
    std::cout << "Start simulation ..." << std::endl;
    #endif

    analyzer.register_simulation_start();
    sc_start(2500, SC_NS);
    analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    analyzer.print_report();
  
    return (0);
}
