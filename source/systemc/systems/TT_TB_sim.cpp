/*!
 * @file TT_TB_sim.cpp
 * @author Christian Amstutz
 * @date August 17, 2015

 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "tt_tb.hpp"
#include "../TT_configuration/track_trigger_config.hpp"
#include "../TT_configuration/baseline_config.hpp"

#include "sc_analyzer.hpp"

#include <systemc.h>

#include <iostream>
#include <sstream>
#include <utility>

int sc_main(int argc, char *agv[])
{
    // Setting up analyzer for SystemC simulation
    sc_analyzer analyzer;
    analyzer.register_model_setup_start();

    // Configure model
    track_trigger_config test_config = baseline_config();

    test_config.hit_generator.input_file = "data/hits.txt";
    tt_tb testbench("TT_TB", test_config);

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.LHC_clock, "LHC_clock");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[0].demultiplexer.bunch_crossing_request, "DO0.bx_request");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[1].demultiplexer.bunch_crossing_request, "DO1.bx_request");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[2].demultiplexer.bunch_crossing_request, "DO2.bx_request");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[3].demultiplexer.bunch_crossing_request, "DO3.bx_request");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[0].bunch_request_sig, "DO0.bx_request_sig");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[1].bunch_request_sig, "DO1.bx_request_sig");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[2].bunch_request_sig, "DO2.bx_request_sig");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[3].bunch_request_sig, "DO3.bx_request_sig");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[0].stub_buffer.bunch_crossing_select, "DO0.bx_select");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[1].stub_buffer.bunch_crossing_select, "DO1.bx_select");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[2].stub_buffer.bunch_crossing_select, "DO2.bx_select");
    sc_trace(trace_file, testbench.trigger_tower_0.dataOrganizers[3].stub_buffer.bunch_crossing_select, "DO3.bx_select");

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
