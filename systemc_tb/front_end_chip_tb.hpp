/*!
 * @file front_end_chip_tb.hpp
 * @author Christian Amstutz
 * @date Jan 27, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>

#include "systemc.h"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/front_end_chip.hpp"
#include "../systemc/stub.hpp"

/*!
 * @brief
 */
class front_end_chip_tb : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------

  // ----- Local Channel Declarations ------------------------------------------
  sc_signal<bool> en_sig;
  sc_fifo<stub> stub_input_sig;
  sc_signal<bool> hit1_dv_sig;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit1_data_sig;
  sc_signal<bool> hit2_dv_sig;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit2_data_sig;
  sc_signal<bool> hit3_dv_sig;
  sc_signal<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit3_data_sig;

  // ----- Process Declarations ------------------------------------------------
  void generate_stubs();
  void analyse_FE_data();
  void analyse_FE_dv();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  sc_clock LHC_clock;
  front_end_chip dut_front_end_chip;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  front_end_chip_tb(sc_module_name _name);
  SC_HAS_PROCESS(front_end_chip_tb);

private:

};
