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

#include "tt_tb.hpp"

#include "../libraries/systemc_helpers/sc_analyzer/sc_analyzer.hpp"

#include <systemc.h>

#include <iostream>
#include <sstream>
#include <utility>

int sc_main(int argc, char *agv[])
{
    // Setting up analyzer for SystemC simulation
    sc_analyzer analyzer;
    analyzer.register_model_setup_start();

    tt_tb testbench("TT_TB");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------

    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB");
    //trace_file->delta_cycles(true);

    sc_trace(trace_file, testbench.LHC_clock, "LHC_clock");

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
