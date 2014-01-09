/*!
 * @file SensorModule.hpp
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

#include "TT_configuration.hpp"
#include "FrontEndChip.hpp"
#include "DataConcentratorChip.hpp"
#include "FE_DataFormat.hpp"

/*!
 * @brief
 */
class SensorModule : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_out<int> data_output;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  FrontEndChip *frontEndChip[NR_FRONTENDCHIP_PER_MODULE];
  DataConcentratorChip dataConcentrator;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  SensorModule(sc_module_name _name);
  SC_HAS_PROCESS(SensorModule);

private:

};
