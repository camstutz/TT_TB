/*!
 * @file data_concentrator.hpp
 * @author Christian Amstutz
 * @date Jan 27, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <iostream>

#include <systemc.h>

#include "TT_configuration.hpp"

/*!
 * @brief
 */
class data_concentrator : public sc_module {

public:
  // ----- Port Declarations ---------------------------------------------------
  sc_in<bool> clk;
  sc_in<bool> rst;

  sc_in<bool> hit0_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit0_data;
  sc_in<bool> hit1_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit1_data;
  sc_in<bool> hit2_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit2_data;
  sc_in<bool> hit3_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit3_data;
  sc_in<bool> hit4_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit4_data;
  sc_in<bool> hit5_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit5_data;
  sc_in<bool> hit6_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit6_data;
  sc_in<bool> hit7_dv;
  sc_in<sc_bv<FE_CHIP_OUTPUT_WIDTH> > hit7_data;

  sc_out<sc_bv<DO_OUTPUT_WIDTH> > do_output;


  // ----- Local Channel Declarations ------------------------------------------
  sc_signal<sc_uint<3> > clock_phase;

  // ----- Process Declarations ------------------------------------------------
  void advance_clock_phase();
  void read_FE_chips();
  void write_DO_output();

  // ----- Other Method Declarations -------------------------------------------

  // ----- Module Instantiations -----------------------------------------------

  // ----- Constructor ---------------------------------------------------------
  data_concentrator(sc_module_name _name);
  SC_HAS_PROCESS(data_concentrator);

private:
  typedef sc_bv<20> long_stub;
  const long_stub empty_slot;
  std::vector<long_stub> stub_buffer;
  //! todo: change sc_bv size to constants
  sc_bv<32*8> output_buffer;

  void create_output_buffer();
};
