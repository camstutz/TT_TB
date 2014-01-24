/*!
 * @file front_end_chip.hpp
 * @author Christian Amstutz
 * @date Jan 24, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <algorithm>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class front_end_chip : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<bool> en;
  sc_fifo_in<stub> stub_input;
  sc_out<bool> hit1_dv;
  sc_out<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit1_data;
  sc_out<bool> hit2_dv;
  sc_out<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit2_data;
  sc_out<bool> hit3_dv;
  sc_out<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit3_data;

  // ----- Local Channel Declarations ------------------------------------------
  sc_fifo<stub> selected_stubs;

  // ----- Process Declarations ------------------------------------------------
  void prioritize_hits();
  void write_hits();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  front_end_chip(sc_module_name _name);
  SC_HAS_PROCESS(front_end_chip);
  void end_of_elaboration();

private:

};
