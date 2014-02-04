/*!
 * @file front_end_chip_tb.hpp
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

#include <iostream>
#include <sstream>
#include <array>

#include "systemc.h"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/front_end_chip.hpp"
#include "../systemc/stub.hpp"

/*!
 * @brief
 */
class front_end_chip_tb : public sc_module {

public:
  typedef struct {
    sc_signal<bool> *dv;
    sc_signal<stub> *data;
  } fe_signal_t;

  // ----- Port Declarations ---------------------------------------------------

  // ----- Local Channel Declarations ------------------------------------------
  sc_signal<bool> en_sig;
  sc_fifo<stub> stub_input_sig;
  std::array<fe_signal_t, MAX_HITS_PER_FE_CHIP> fe_out_signals;

  // ----- Process Declarations ------------------------------------------------
  void generate_stubs();
  void analyse_FE_data();
  void analyse_FE_dv();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  sc_clock LHC_clock;
  front_end_chip dut_front_end_chip;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  front_end_chip_tb(sc_module_name _name);
  SC_HAS_PROCESS(front_end_chip_tb);
  ~front_end_chip_tb();
  void end_of_elaboration();

private:
  std::ostringstream log_buffer;

};
