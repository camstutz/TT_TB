/*!
 * @file hit_generator_test.hpp
 * @author Christian
 * @date Jan 15, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <sstream>

#include "systemc.h"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/hit_generator.hpp"
#include "../systemc/stub.hpp"

/*!
 * @brief
 */
class hit_generator_tb : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------

  // ----- Local Channel Declarations ------------------------------------------
  std::vector<std::vector<std::vector<std::vector<sc_fifo<stub> *> > > > hit_signals;

  // ----- Process Declarations ------------------------------------------------
  void check_output();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  hit_generator dut_hit_generator;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  hit_generator_tb(sc_module_name _name);
  SC_HAS_PROCESS(hit_generator_tb);
  ~hit_generator_tb();

private:
  std::ostringstream log_buffer;

};
