/*!
 * @file front_end_chip.hpp
 * @author Christian Amstutz
 * @date Feb 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <array>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class front_end_chip : public sc_module {

public:
  typedef struct {
    sc_out<bool> *dv;
    sc_out<stub> *data;
  } hit_out_t;

  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<bool> en;

  sc_fifo_in<stub> stub_input;

  std::array<hit_out_t, MAX_HITS_PER_FE_CHIP> hit_outputs;

  // ----- Local Channel Declarations ------------------------------------------
  sc_fifo<stub> selected_stubs;

  // ----- Process Declarations ------------------------------------------------
  void prioritize_hits();
  void write_hits();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  front_end_chip(const sc_module_name _name);
  SC_HAS_PROCESS(front_end_chip);
  void end_of_elaboration();

private:

};
