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
//#include "../TT_configuration/baseline_config.hpp"
//#include "../TT_configuration/simple_tower_27_config.hpp"
//#include "../TT_configuration/dsd/dsd_config.hpp"
#include "../TT_configuration/debug_2x2/debug_2x2_config.hpp"

#include "sc_analyzer.hpp"

#include <systemc.h>

#include <iostream>
#include <sstream>
#include <utility>

//size_analyzer simulation_size;

int sc_main(int argc, char *agv[])
{
    // Setting up analyzer for SystemC simulation
    sc_analyzer analyzer;
    analyzer.register_model_setup_start();

    // Configure model
    //track_trigger_config test_config = simple_tower_27_config();
    //track_trigger_config test_config = dsd_config();
    track_trigger_config test_config = debug_2x2_config();

    test_config.hit_generator.input_file = "source/systemc/TT_configuration/debug_2x2/hits_debug_8track.txt";

    tt_tb testbench("TT_TB", test_config);
    //testbench.print_system();

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.LHC_clock, "LHC_clock");

    // ----- Start simulation --------------------------------------------------

    std::cout << "Model constructed." << std::endl;
    std::cout << "Start simulation ..." << std::endl;

    analyzer.register_simulation_start();
    sc_start(10000, SC_NS);
    analyzer.register_simulation_end();

    sc_close_vcd_trace_file(trace_file);

    #ifdef DEBUG
    std::cout << "Simulation ended." << std::endl;
    #endif

    analyzer.print_report();
    std::cout << std::endl;
    //simulation_size.print_report();

    return (0);
}
