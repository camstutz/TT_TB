/*!
 * @file data_concentrator.cpp
 * @author Christian Amstutz
 * @date Jan 31, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */

data_concentrator::data_concentrator(sc_module_name _name) :
    sc_module(_name) ,
    clk("clk"),
    rst("rst"),
    hit0_dv("hit0_dv"),
    hit0_data("hit0_data"),
    hit1_dv("hit1_dv"),
    hit1_data("hit1_data"),
    hit2_dv("hit2_dv"),
    hit2_data("hit2_data"),
    hit3_dv("hit3_dv"),
    hit3_data("hit3_data"),
    hit4_dv("hit4_dv"),
    hit4_data("hit4_data"),
    hit5_dv("hit5_dv"),
    hit5_data("hit5_data"),
    hit6_dv("hit6_dv"),
    hit6_data("hit6_data"),
    hit7_dv("hit7_dv"),
    hit7_data("hit7_data"),
    do_output("do_output"),
    empty_slot( (false, sc_bv<19>(0)) ) {

  // ----- Process registration ------------------------------------------------
  SC_THREAD(advance_clock_phase);
    sensitive << clk.pos();
  SC_THREAD(read_FE_chips);
    sensitive << clk.pos();
  SC_THREAD(write_DO_output);
    sensitive << clk.pos();

  // ----- Module variable initialization --------------------------------------
  clock_phase = 0;

  // ----- Module instance / channel binding -----------------------------------

  return;
}

// *****************************************************************************
void data_concentrator::read_FE_chips() {

  while(1) {

    wait();

    if (hit0_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(0), hit0_data.read()) );
    }
    if (hit1_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(1), hit1_data.read()) );
    }
    if (hit2_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(2), hit2_data.read()) );
    }
    if (hit3_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(3), hit3_data.read()) );
    }
    if (hit4_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(4), hit4_data.read()) );
    }
    if (hit5_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(5), hit5_data.read()) );
    }
    if (hit6_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(6), hit6_data.read()) );
    }
    if (hit7_dv == true) {
      stub_buffer.push_back( (true, sc_bv<3>(clock_phase.read()), sc_bv<3>(7), hit7_data.read()) );
    }
  }
}

// *****************************************************************************
void data_concentrator::advance_clock_phase() {

  while(1) {
    wait();
    clock_phase.write(clock_phase.read() + 1);
    if (clock_phase.read() == 7) {
      create_output_buffer();
      stub_buffer.clear();
    }
  }
}

// *****************************************************************************
void data_concentrator::write_DO_output() {

  //! todo: change constants numbers to parameter
  while(1) {
    wait();

    sc_bv<DO_OUTPUT_WIDTH> output_val;
    output_val(DO_OUTPUT_WIDTH-3,0) = output_buffer((clock_phase.read()+1)*(DO_OUTPUT_WIDTH-2)-1, clock_phase.read()*(DO_OUTPUT_WIDTH-2));
    output_val[DO_OUTPUT_WIDTH-2] = 0;
    if (clock_phase.read() == 0) {
      output_val[DO_OUTPUT_WIDTH-1] = 1;
      do_output.write( output_val );
    }
    else {
      output_val[DO_OUTPUT_WIDTH-1] =  0;
      do_output.write( output_val );
    }
  }
}

// *****************************************************************************
void data_concentrator::create_output_buffer() {

  //! todo: change constants numbers to parameter

  // Buffer size is only 12 in real system
  if (stub_buffer.size() > 12) {
    std::cout << "data_concentrator: Stub buffer overflow!" << std::endl;
  }
  stub_buffer.resize(12, empty_slot);

  for(unsigned short i; i<12; i++) {
    output_buffer( (i+1)*20-1, i*20) = stub_buffer[i];
  }

  return;
}
