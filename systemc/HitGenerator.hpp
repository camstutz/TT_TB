/*!
 * @file HitGenerator.hpp
 * @author Christian Amstutz
 * @date Dec 10, 2013
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#pragma once

#include <string>
#include <systemc.h>
//#include <iostream>
//#include <fstream>
#include <sstream>

#include "HitEvent.hpp"

/*!
 * @brief
 */
class HitGenerator : public sc_module {

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
  HitGenerator(sc_module_name _name, std::string hitFileName);
  SC_HAS_PROCESS(HitGenerator);

private:

};
