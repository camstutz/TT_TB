/*!
 * @file sensor_module.hpp
 * @author Christian Amstutz
 * @date Feb 5, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <sstream>
#include <array>

#include <systemc.h>

#include "stub.hpp"
#include "TT_configuration.hpp"
#include "front_end_chip.hpp"
#include "data_concentrator.hpp"

/*!
 * @brief
 */
class sensor_module : public sc_module {

public:
  typedef sc_fifo_in<stub> stub_in_t;
  typedef struct {
    sc_signal<bool> *dv;
    sc_signal<stub> *data;
  } hit_signal_t;
  typedef std::array<hit_signal_t, MAX_HITS_PER_FE_CHIP> fe_signal_t;

  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  std::array<stub_in_t*, NR_FE_CHIP_PER_MODULE> stub_inputs;

  //! todo: think about the data type of dc_out, generic ?
  sc_out<sc_bv<DC_OUTPUT_WIDTH> > dc_out;

  // ----- Local Channel Declarations ------------------------------------------
  std::array<fe_signal_t, NR_FE_CHIP_PER_MODULE> fe_out_signals;
  sc_signal<bool> true_sig;

  // ----- Process Declarations ------------------------------------------------

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------
  std::array<front_end_chip*, NR_FE_CHIP_PER_MODULE> front_end_chips;
  data_concentrator dataConcentrator;

  // ----- Constructor ---------------------------------------------------------
  /*!
   * Constructor:
   */
  sensor_module(const sc_module_name _name);
  SC_HAS_PROCESS(sensor_module);

private:

};
