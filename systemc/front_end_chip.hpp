/*!
 * @file front_end_chip.hpp
 * @author Christian Amstutz
 * @date Jan 9, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "TT_configuration.hpp"
#include "stub.hpp"
#include "FE_DataFormat.hpp"

/*!
 * @brief
 */
class front_end_chip : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<stub> stub_input;
  //sc_out<sc_bv<FE_CHIP_OUTPUT_WIDTH> > data_output;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  front_end_chip(sc_module_name _name);
  SC_HAS_PROCESS(front_end_chip);

private:

};
