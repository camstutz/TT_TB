/*!
 * @file TT_TB_testbench.cpp
 * @author Christian Amstutz
 * @date Jan 15, 2014
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

int sc_main(int argc, char *agv[]) {

  // ----- Channel declarations ------------------------------------------------

  // ----- Variable declarations -----------------------------------------------

  // ----- Module instance declarations ----------------------------------------

  hit_generator_tb hit_generator_tb("Hit_Generator_TB");

  // ----- Time unit / resolution setup ----------------------------------------

  // ----- Set up tracing ------------------------------------------------------

  // ----- Start simulation ----------------------------------------------------

  std::cout << std::endl << "Start test bench ..." << std::endl << std::endl;

  sc_start();

  std::cout << std::endl << "Test bench ended." << std::endl;

  return 0;
}
