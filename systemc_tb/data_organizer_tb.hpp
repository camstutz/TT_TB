/*!
 * @file data_organizer_tb.hpp
 * @author Christian Amstutz
 * @date Feb 7, 2014
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
#include "../systemc/data_organizer.hpp"
#include "../systemc/stub_ext.hpp"

/*!
 * @brief
 */
class data_organizer_tb : public sc_module {

public:
  typedef struct {
    sc_signal<bool> *dv;
    sc_signal<stub_ext> *data;
  } front_end_in_t;
  typedef std::array<front_end_in_t, MAX_HITS_PER_FE_CHIP> front_end_signal_t;

  // ----- Port Declarations ---------------------------------------------------

  // ----- Local Channel Declarations ------------------------------------------
  sc_signal<bool> rst;
  std::array<front_end_signal_t, NR_FE_CHIP_PER_MODULE> fe_signals;
  sc_signal<sc_bv<DC_OUTPUT_WIDTH> > dc_output;

  // ----- Process Declarations ------------------------------------------------
  void write_stream();
  void print_output();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  sc_clock LHC_clock;
  data_organizer dut_data_organizer;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  data_organizer_tb(sc_module_name _name);
  SC_HAS_PROCESS(data_organizer_tb);
  ~data_organizer_tb();
  void end_of_elaboration();

private:
  std::ostringstream log_buffer;
};
