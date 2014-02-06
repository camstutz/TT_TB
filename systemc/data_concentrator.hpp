/*!
 * @file data_concentrator.hpp
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

#include <array>
#include <iostream>
#include <sstream>

#include <systemc.h>

#include "TT_configuration.hpp"
#include "nbits.hpp"
#include "stub.hpp"

/*!
 * @brief
 */
class data_concentrator : public sc_module {

public:
  typedef struct {
    sc_in<bool> *dv;
    sc_in<stub> *data;
  } fe_in_t;
  typedef std::array<fe_in_t, MAX_HITS_PER_FE_CHIP> fe_port_t;
  typedef std::array<fe_port_t, NR_FE_CHIP_PER_MODULE> fe_field_t;

  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<bool> rst;
  fe_field_t fe_stub_in;

  //! todo: think about the data type of dc_out, generic ?
  sc_out<sc_bv<DC_OUTPUT_WIDTH> > dc_out;

  // ----- Local Channel Declarations ------------------------------------------
  //! todo: change width to generic
  sc_signal<sc_uint<3> > clock_phase;

  // ----- Process Declarations ------------------------------------------------
  void advance_clock_phase();
  void read_FE_chips();
  void write_output();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  data_concentrator(sc_module_name _name);
  SC_HAS_PROCESS(data_concentrator);

private:
  //! todo: make long_stub generic, probably an object
  typedef sc_bv<20> long_stub;
  const long_stub empty_slot;
  std::vector<long_stub> stub_buffer;
  sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES> output_buffer;

  void create_output_buffer();
};
