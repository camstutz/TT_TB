/*!
 * @file front_end_chip.cpp
 * @author Christian Amstutz
 * @date Jan 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "front_end_chip.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip
 *
 * The module is sensitive to ....
 */

front_end_chip::front_end_chip(sc_module_name _name)
    : sc_module(_name),
      clk("clk"),
      en("en"),
      stub_input("stub_in"),
      hit1_dv("hit1_dv"),
      hit1_data("hit1_data"),
      hit2_dv("hit2_dv"),
      hit2_data("hit2_data"),
      hit3_dv("hit3_dv"),
      hit3_data("hit3_data"),
      selected_stubs("sel_stubs", NR_HITS_PER_FE_CHIP) {

  // ----- Process registration ------------------------------------------------


  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  return;
}

// *****************************************************************************
void front_end_chip::end_of_elaboration() {

  SC_THREAD(prioritize_hits);
    sensitive << stub_input.data_written_event();
  SC_THREAD(write_hits);
    sensitive << clk.posedge_event(); //selected_stubs.data_written_event();
}

// *****************************************************************************
void front_end_chip::prioritize_hits() {

  while(1) {
    wait();
    //if(!clk.event()) {
    //  wait(clk.posedge_event());
    //}

    stub act_stub;
    for(int i=0; i <= std::min(stub_input.num_available(), NR_HITS_PER_FE_CHIP); i++) {
      stub_input.nb_read(act_stub);
      selected_stubs.nb_write(act_stub);
    }
    while(stub_input.nb_read(act_stub)) {};
  }

}

// *****************************************************************************
void front_end_chip::write_hits() {

  while (1) {
    wait();

    stub read_stub;
    sc_bv<FE_CHIP_OUTPUT_WIDTH> output_hit;

    hit1_dv.write(false);
    hit2_dv.write(false);
    hit3_dv.write(false);

    if(selected_stubs.nb_read(read_stub)) {
      hit1_dv.write(true);
      output_hit = read_stub.getAddress() << 5;
      //output_hit = ((0xFF & read_stub.getAddress()) << 5 ) &
      //             ( 0x1F & read_stub.getBend());
      hit1_data.write(output_hit);
      std::cout << sc_time_stamp() << " write_hits(1): 0x" << output_hit << std::endl;
    }
    if(selected_stubs.nb_read(read_stub)) {
      hit2_dv.write(true);
      output_hit = read_stub.getAddress() << 5;
      //output_hit = ((0xFF & read_stub.getAddress()) << 5 ) &
      //             ( 0x1F & read_stub.getBend());
      hit2_data.write(output_hit);
      std::cout << sc_time_stamp() << " write_hits(2): 0x" << output_hit << std::endl;
    }
    if(selected_stubs.nb_read(read_stub)) {
      hit3_dv.write(true);
      output_hit = read_stub.getAddress() << 5;
      //output_hit = ((0xFF & read_stub.getAddress()) << 5 ) &
      //             ( 0x1F & read_stub.getBend());
      hit3_data.write(output_hit);
      std::cout << sc_time_stamp() << " write_hits(3): 0x" << output_hit << std::endl;
    }
  }

}
