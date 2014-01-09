/*!
 * @file DataOrganizerChip.hpp
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
class DataOrganizerChip : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  DataOrganizerChip(sc_module_name _name);
  SC_HAS_PROCESS(DataOrganizerChip);

private:

};
