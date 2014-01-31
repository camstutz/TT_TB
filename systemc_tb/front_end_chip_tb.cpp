/*!
 * @file front_end_chip_tb.cpp
 * @author Christian Amstutz
 * @date Jan 24, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "front_end_chip_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

front_end_chip_tb::front_end_chip_tb(sc_module_name _name) :
    sc_module(_name),
    LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true),
    dut_front_end_chip("Front_End_Chip_DUT"),
    en_sig("en"),
    stub_input_sig("stub_input"),
    hit1_dv_sig("hit1_dv"),
    hit1_data_sig("hit1_data"),
    hit2_dv_sig("hit2_dv"),
    hit2_data_sig("hit2_data"),
    hit3_dv_sig("hit3_dv"),
    hit3_data_sig("hit3_data") {

  // ----- Creation and binding of signals -------------------------------------
  dut_front_end_chip.clk(LHC_clock);
  dut_front_end_chip.en(en_sig);
  dut_front_end_chip.stub_input(stub_input_sig);
  dut_front_end_chip.hit1_dv(hit1_dv_sig);
  dut_front_end_chip.hit1_data(hit1_data_sig);
  dut_front_end_chip.hit2_dv(hit2_dv_sig);
  dut_front_end_chip.hit2_data(hit2_data_sig);
  dut_front_end_chip.hit3_dv(hit3_dv_sig);
  dut_front_end_chip.hit3_data(hit3_data_sig);

  // ----- Process registration ------------------------------------------------
  SC_THREAD(generate_stubs);
  SC_THREAD(analyse_FE_data);
    sensitive << hit1_dv_sig << hit2_dv_sig << hit3_dv_sig;
  SC_THREAD(analyse_FE_dv);
    sensitive << hit1_dv_sig << hit2_dv_sig << hit3_dv_sig;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

    log_buffer << std::endl
               << "Simulation Output of Front End Chip TB:" << std::endl
               << "*******************************************" << std::endl;

  return;
}

// *****************************************************************************
front_end_chip_tb::~front_end_chip_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void front_end_chip_tb::generate_stubs() {

  stub stim_stub;

  wait(60, SC_NS);
  en_sig.write(1);
  stim_stub.setAddress(255);
  stim_stub.setBend(1);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;

  wait(32, SC_NS);
  stim_stub.setAddress(100);
  stim_stub.setBend(2);
  stub_input_sig.write(stim_stub);
  std::cout << sc_time_stamp() << " " << stim_stub << std::endl;
  stim_stub.setAddress(120);
  stim_stub.setBend(3);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;

  wait(1, SC_NS);
  stim_stub.setAddress(101);
  stim_stub.setBend(4);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;
  wait(1, SC_NS);
  stim_stub.setAddress(101);
  stim_stub.setBend(5);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;

  wait(25, SC_NS);
  stim_stub.setAddress(1);
  stim_stub.setBend(6);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;

  wait(25, SC_NS);
  stim_stub.setAddress(12);
  stim_stub.setBend(7);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;
  stim_stub.setAddress(13);
  stim_stub.setBend(8);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << " " << stim_stub << std::endl;

  return;
}

// *****************************************************************************
void front_end_chip_tb::analyse_FE_data() {

  sc_bv<13> read_hit;

  while(1) {
    wait();
    if(hit1_dv_sig.read() == true) {
      read_hit = hit1_data_sig.read();
      log_buffer << sc_time_stamp() <<" Hit1: "
                 << " " << read_hit.to_string()
                 << " (0x" << std::hex << read_hit << ")"
                 << " - Address: " << (read_hit >> 5)
                 << " Bend: " << (read_hit & 0x01F)
                 << std::endl;
    }
    if(hit2_dv_sig.read() == true) {
      read_hit = hit2_data_sig.read();
      log_buffer << sc_time_stamp() <<" Hit1: "
                 << " " << read_hit.to_string()
                 << " (0x" << std::hex << read_hit << ")"
                 << " - Address: " << (read_hit >> 5)
                 << " Bend: " << (read_hit & 0x01F)
                 << std::endl;
    }
    if(hit3_dv_sig.read() == true) {
      read_hit = hit3_data_sig.read();
      log_buffer << sc_time_stamp() <<" Hit1: "
                 << " " << read_hit.to_string()
                 << " (0x" << std::hex << read_hit << ")"
                 << " - Address: " << (read_hit >> 5)
                 << " Bend: " << (read_hit & 0x01F)
                 << std::endl;
    }
  }

  return;
}

// *****************************************************************************
void front_end_chip_tb::analyse_FE_dv() {

  while(1) {
    wait();
    log_buffer << sc_time_stamp() << ": DV" << std::endl;
  }

}
