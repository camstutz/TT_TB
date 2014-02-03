/*!
 * @file hit_generator.hpp
 * @author Christian Amstutz
 * @date Feb 3, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <queue>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "HitEvent.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class hit_generator : public sc_module {

public:
  typedef sc_fifo_out<stub> *hit_out_t;
  typedef std::vector<hit_out_t> z_dim_out_t;
  typedef std::vector<z_dim_out_t> phi_dim_out_t;
  typedef std::vector<phi_dim_out_t> layer_dim_out_t;
  typedef std::vector<layer_dim_out_t> hit_out_bus_t;

  // ----- Port Declarations ---------------------------------------------------
  hit_out_bus_t hit_outputs;

  // ----- Local Channel Declarations ------------------------------------------

  // ----- Process Declarations ------------------------------------------------
  void schedule_hits();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  hit_generator(sc_module_name _name, std::string hitFileName);
  SC_HAS_PROCESS(hit_generator);

private:
  std::queue<HitEvent> hit_queue;
  int readFile(const std::string &hit_file);
};
