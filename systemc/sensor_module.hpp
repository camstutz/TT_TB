/*!
 * @file sensor_module.hpp
 * @author Christian Amstutz
 * @date Jan 13, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <sstream>
#include <vector>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "front_end_chip.hpp"
#include "data_concentrator.hpp"

/*!
 * @brief
 */
class sensor_module : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  std::vector<sc_fifo_in<stub> *> stub_inputs;
  sc_out<int> data_output;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  front_end_chip *front_end_chips[NR_FRONTENDCHIP_PER_MODULE];
  data_concentrator dataConcentrator;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  sensor_module(sc_module_name _name);
  SC_HAS_PROCESS(sensor_module);

private:
  //std::vector<sc_signal<stub> *> stub_signals;

};
