/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <systemc.h>
#include <iostream>
#include <string>

#include "hit_generator_tb.hpp"
#include "front_end_chip_tb.hpp"
#include "data_concentrator_tb.hpp"
#include "data_organizer_tb.hpp"
#include "am_system_tb.hpp"

int sc_main(int argc, char *agv[])
{
    // ----- Channel declarations ----------------------------------------------

    // ----- Variable declarations ---------------------------------------------

    // ----- Module instance declarations --------------------------------------

    //hit_generator_tb hit_generator_tb("Hit_Generator_TB");
    //front_end_chip_tb front_end_chip_tb("Front_End_Chip_TB");
    //data_concentrator_tb data_concentrator_tb("Data_Concentrator_TB");
    //data_organizer_tb data_organizer_tb("Data_Organizer_TB");
    am_system_tb am_system_tb("AM_System");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------
    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB_testbench");

//    sc_trace(trace_file, data_concentrator_tb.LHC_clock, "DC_clock");
//    sc_trace(trace_file, data_concentrator_tb.dc_output, "dc_out");
//    sc_trace(trace_file, data_concentrator_tb.dut_data_concentrator.clock_phase, "clk_phase");
//    sc_trace(trace_file, data_concentrator_tb.dut_data_concentrator.stub_buffer_write_sel, "write_sel");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(0,0), "FE_0-0");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(0,1), "FE_0-1");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(1,0), "FE_1-0");
//    sc_trace(trace_file, data_concentrator_tb.fe_signals.at(1,1), "FE_1-1");

    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

    sc_start(600, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    std::cout << std::endl << "Test bench ended." << std::endl;

    return (0);
}
