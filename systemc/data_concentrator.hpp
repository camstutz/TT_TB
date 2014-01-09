/*!
 * @file data_concentrator.hpp
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
#include "FE_DataFormat.hpp"
#include "DC_DataFormat.hpp"

/*!
 * @brief
 */
class data_concentrator : public sc_module {

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
  data_concentrator(sc_module_name _name);
  SC_HAS_PROCESS(data_concentrator);

private:

};
