/*!
 * @file hit_generator.hpp
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

#include <string>
#include <systemc.h>
#include <sstream>

#include "TT_configuration.hpp"
#include "HitEvent.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class hit_generator : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_out<stub> data_output[NR_DETECTOR_LAYERS][NR_DETECTOR_PHI][NR_DETECTOR_Z][NR_FRONTENDCHIP_PER_MODULE];

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  hit_generator(sc_module_name _name, std::string hitFileName);
  SC_HAS_PROCESS(hit_generator);

private:

};
