/*!
 * @file sensor_module.hpp
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
#include "front_end_chip.hpp"
#include "data_concentrator.hpp"
#include "FE_DataFormat.hpp"

/*!
 * @brief
 */
class sensor_module : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<stub> stub_input[NR_FRONTENDCHIP_PER_MODULE];
  sc_out<int> data_output;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  front_end_chip *frontEndChip[NR_FRONTENDCHIP_PER_MODULE];
  data_concentrator dataConcentrator;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  sensor_module(sc_module_name _name);
  SC_HAS_PROCESS(sensor_module);

private:

};
