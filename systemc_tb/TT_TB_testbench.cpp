/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
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

int sc_main(int argc, char *agv[])
{
    // ----- Channel declarations ----------------------------------------------

    // ----- Variable declarations ---------------------------------------------

    // ----- Module instance declarations --------------------------------------

    //hit_generator_tb hit_generator_tb("Hit_Generator_TB");
    //front_end_chip_tb front_end_chip_tb("Front_End_Chip_TB");
    //data_concentrator_tb data_concentrator_tb("Data_Concentrator_TB");
    data_organizer_tb data_organizer_tb("Data_Organizer_TB");

    // ----- Time unit / resolution setup --------------------------------------

    // ----- Set up tracing ----------------------------------------------------
    sc_trace_file *trace_file;
    trace_file=sc_create_vcd_trace_file("TT_TB_testbench");

    sc_trace(trace_file, data_organizer_tb.fe_streams, "fe_stream");
    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stream_in[0], "input");
    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table_sel, "stub_table_sel");
    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.clock_phase, "clock_phase");
    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_out, "output");

//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][0][0], "stubtable0_0,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][0][1], "stubtable0_0,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][0][2], "stubtable0_0,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][1][0], "stubtable0_1,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][1][1], "stubtable0_1,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][1][2], "stubtable0_1,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][2][0], "stubtable0_2,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][2][1], "stubtable0_2,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][2][2], "stubtable0_2,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][3][0], "stubtable0_3,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][3][1], "stubtable0_3,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][3][2], "stubtable0_3,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][4][0], "stubtable0_4,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][4][1], "stubtable0_4,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][4][2], "stubtable0_4,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][5][0], "stubtable0_5,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][5][1], "stubtable0_5,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][5][2], "stubtable0_5,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][6][0], "stubtable0_6,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][6][1], "stubtable0_6,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][6][2], "stubtable0_6,2");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][7][0], "stubtable0_7,0");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][7][1], "stubtable0_7,1");
//    sc_trace(trace_file, data_organizer_tb.dut_data_organizer.stub_table[0][7][2], "stubtable0_7,2");

//    sc_trace(trace_file,data_concentrator_tb.LHC_clock,"DC_clock");
//    sc_trace(trace_file,data_concentrator_tb.dc_output,"dc_out");
//    sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][1].dv,"dv1");
//    sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][1].data,"data1");
//    sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][2].dv,"dv2");
//    sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][2].data,"data2");

    // ----- Start simulation --------------------------------------------------

    std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

    sc_start(600, SC_NS);

    sc_close_vcd_trace_file(trace_file);
    std::cout << std::endl << "Test bench ended." << std::endl;

    return (0);
}
