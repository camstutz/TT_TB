/*!
 * @file data_concentrator_tb.hpp
 * @author Christian Amstutz
 * @date Jan 31, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <sstream>

#include "systemc.h"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/data_concentrator.hpp"

/*!
 * @brief
 */
class data_concentrator_tb : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------

  // ----- Local Channel Declarations ------------------------------------------
  sc_signal<bool> rst;

  sc_signal<bool> hit0_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit0_data;
  sc_signal<bool> hit1_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit1_data;
  sc_signal<bool> hit2_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit2_data;
  sc_signal<bool> hit3_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit3_data;
  sc_signal<bool> hit4_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit4_data;
  sc_signal<bool> hit5_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit5_data;
  sc_signal<bool> hit6_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit6_data;
  sc_signal<bool> hit7_dv;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit7_data;

  sc_signal<sc_bv<DO_OUTPUT_WIDTH> > do_output;
  // ----- Process Declarations ------------------------------------------------
  void generate_hit_data();
  void print_output();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  sc_clock LHC_clock;
  data_concentrator dut_data_concentrator;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  data_concentrator_tb(sc_module_name _name);
  SC_HAS_PROCESS(data_concentrator_tb);
  ~data_concentrator_tb();

private:
  std::ostringstream log_buffer;

};
