/*!
 * @file DataConcentratorChip.hpp
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

#include "TT_configuration.hpp"
#include "FE_DataFormat.hpp"
#include "DC_DataFormat.hpp"

/*!
 * @brief
 */
class DataConcentratorChip : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<int>  data_input;  //! @todo move number configuration to constructor
  sc_out<int> data_output;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  DataConcentratorChip(sc_module_name _name);
  SC_HAS_PROCESS(DataConcentratorChip);

private:

};
