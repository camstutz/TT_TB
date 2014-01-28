/*!
 * @file data_concentrator_tb.cpp
 * @author Christian Amstutz
 * @date Jan 27, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

data_concentrator_tb::data_concentrator_tb(sc_module_name _name) :
    sc_module(_name),
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
    LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true),
    dut_data_concentrator("Data_Concentrator_DUT") {

  // ----- Creation and binding of signals -------------------------------------
  dut_data_concentrator.clk(LHC_clock);
  dut_data_concentrator.rst(rst);

  dut_data_concentrator.hit0_dv(hit0_dv);
  dut_data_concentrator.hit0_data(hit0_data);
  dut_data_concentrator.hit1_dv(hit1_dv);
  dut_data_concentrator.hit1_data(hit1_data);
  dut_data_concentrator.hit2_dv(hit2_dv);
  dut_data_concentrator.hit2_data(hit2_data);
  dut_data_concentrator.hit3_dv(hit3_dv);
  dut_data_concentrator.hit3_data(hit3_data);
  dut_data_concentrator.hit4_dv(hit4_dv);
  dut_data_concentrator.hit4_data(hit4_data);
  dut_data_concentrator.hit5_dv(hit5_dv);
  dut_data_concentrator.hit5_data(hit5_data);
  dut_data_concentrator.hit6_dv(hit6_dv);
  dut_data_concentrator.hit6_data(hit6_data);
  dut_data_concentrator.hit7_dv(hit7_dv);
  dut_data_concentrator.hit7_data(hit7_data);

  dut_data_concentrator.do_output(do_output);

  // ----- Process registration ------------------------------------------------
  SC_THREAD(generate_hit_data);
  SC_THREAD(print_output);
    sensitive << do_output;

  // ----- Module variable initialization --------------------------------------
  hit0_dv = false;
  hit1_dv = false;
  hit2_dv = false;
  hit3_dv = false;
  hit4_dv = false;
  hit5_dv = false;
  hit6_dv = false;
  hit7_dv = false;

  // ----- Module instance / channel binding -----------------------------------

  return;
}

// *****************************************************************************
void data_concentrator_tb::generate_hit_data() {

  //wait(50, SC_NS);
  hit0_dv.write(true);
  hit0_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit0_dv.write(false);

  wait(25, SC_NS);
  hit1_dv.write(true);
  hit1_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;
  hit2_dv.write(true);
  hit2_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit1_dv.write(false);
  hit2_dv.write(false);

  wait(25, SC_NS);
  hit1_dv.write(true);
  hit1_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;
  hit2_dv.write(true);
  hit2_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit1_dv.write(false);
  hit2_dv.write(false);

  wait(25, SC_NS);
  hit1_dv.write(true);
  hit1_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;
  hit2_dv.write(true);
  hit2_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit1_dv.write(false);
  hit2_dv.write(false);

  wait(25, SC_NS);
  hit1_dv.write(true);
  hit1_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;
  hit2_dv.write(true);
  hit2_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit1_dv.write(false);
  hit2_dv.write(false);

  wait(25, SC_NS);
  hit1_dv.write(true);
  hit1_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;
  hit2_dv.write(true);
  hit2_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit1_dv.write(false);
  hit2_dv.write(false);

  wait(25, SC_NS);
  hit1_dv.write(true);
  hit1_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;
  hit2_dv.write(true);
  hit2_data.write("0b1111111100001");
  std::cout << sc_time_stamp() << ": writing data \"0b1111111100001\" " << std::endl;

  wait(25, SC_NS);
  hit1_dv.write(false);
  hit2_dv.write(false);

  return;
}

// *****************************************************************************
void data_concentrator_tb::print_output() {

  while(1) {
    wait();
    std::cout << sc_time_stamp() << ": " << do_output.read() << std::endl;
  }
}
