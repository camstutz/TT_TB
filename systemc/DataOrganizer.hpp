/*!
 * @file DataOrganizer.hpp
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

#include <systemc.h>
//#include <iostream>

/*!
 * @brief
 */
template<int SENSORMODULE_NR>
class DataOrganizer : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<int> sensorInputs[SENSORMODULE_NR];

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  DataOrganizer(sc_module_name _name)
      : sc_module(_name) {

    return;
  }
  SC_HAS_PROCESS(DataOrganizer);

private:

};
