/*!
 * @file FrontEndChip.hpp
 * @author Christian Amstutz
 * @date Dec 6, 2013
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#pragma once

#include <systemc.h>
//#include <iostream>

#include "FE_DataFormat.hpp"

/*!
 * @brief
 */
class FrontEndChip : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_out<int> data_output;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  FrontEndChip(sc_module_name _name);
  SC_HAS_PROCESS(FrontEndChip);

private:

};
