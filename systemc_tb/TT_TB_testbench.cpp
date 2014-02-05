/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date Feb 5, 2014
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

int sc_main(int argc, char *agv[]) {

  // ----- Channel declarations ------------------------------------------------

  // ----- Variable declarations -----------------------------------------------

  // ----- Module instance declarations ----------------------------------------

  hit_generator_tb hit_generator_tb("Hit_Generator_TB");
  front_end_chip_tb front_end_chip_tb("Front_End_Chip_TB");
  data_concentrator_tb data_concentrator_tb("Data_Concentrator_TB");

  // ----- Time unit / resolution setup ----------------------------------------

  // ----- Set up tracing ------------------------------------------------------
  sc_trace_file *trace_file;
  trace_file=sc_create_vcd_trace_file("TT_TB_testbench");

  sc_trace(trace_file,data_concentrator_tb.LHC_clock,"DC_clock");
  sc_trace(trace_file,data_concentrator_tb.dc_output,"dc_out");
  sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][1].dv,"dv1");
  sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][1].data,"data1");
  sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][2].dv,"dv2");
  sc_trace(trace_file,*data_concentrator_tb.fe_signals[1][2].data,"data2");

  // ----- Start simulation ----------------------------------------------------

  std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

  sc_start(1000, SC_NS);

  sc_close_vcd_trace_file(trace_file);
  std::cout << std::endl << "Test bench ended." << std::endl;

  return 0;
}
