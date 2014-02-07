/*!
 * @file data_organizer_tb.cpp
 * @author Christian Amstutz
 * @date Feb 6, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_organizer_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

data_organizer_tb::data_organizer_tb(sc_module_name _name) :
    sc_module(_name),
    rst("rst"),
    LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
    dut_data_concentrator("Data_Concentrator_DUT") {

  // ----- Creation and binding of signals -------------------------------------
  dut_data_concentrator.clk(LHC_clock);
  dut_data_concentrator.rst(rst);

  unsigned int fe_cnt = 0;
  for(front_end_signal_t &fe_signal: fe_signals) {
    unsigned int hit_cnt = 0;
    for (front_end_in_t &fe_in_port: fe_signal) {
      std::ostringstream port_name_dv, port_name_data;
      port_name_dv << "fe" << fe_cnt << "_dv" << hit_cnt;
      fe_in_port.dv = new sc_signal<bool>(port_name_dv.str().c_str());
      port_name_data << "fe" << fe_cnt << "_d" << hit_cnt;
      fe_in_port.data = new sc_signal<stub>(port_name_data.str().c_str());

      dut_data_concentrator.fe_stub_in[fe_cnt][hit_cnt].dv->bind(*fe_in_port.dv);
      dut_data_concentrator.fe_stub_in[fe_cnt][hit_cnt].data->bind(*fe_in_port.data);

      hit_cnt++;
    }
    fe_cnt++;
  }

  dut_data_concentrator.dc_out(dc_output);

  // ----- Process registration ------------------------------------------------
  SC_THREAD(generate_hit_data);
  SC_THREAD(print_output);
    sensitive << dc_output;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  log_buffer << std::endl
             << "Simulation Output of Data Concentrator TB:" << std::endl
             << "*******************************************" << std::endl;

  return;
}

// *****************************************************************************
void data_concentrator_tb::end_of_elaboration() {

  for(front_end_signal_t &fe_signal: fe_signals) {
    for (front_end_in_t &fe_in_port: fe_signal) {
      fe_in_port.dv->write(false);
    }
  }

  return;
}

// *****************************************************************************

data_concentrator_tb::~data_concentrator_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void data_concentrator_tb::generate_hit_data() {

  wait(50, SC_NS);
  write_fe(4,2,255,0);

  wait(25,SC_NS);
  release_fe(4,2);

  wait(200, SC_NS);
  write_fe(1,1,255,31);
  write_fe(1,2,255,31);
  write_fe(1,3,255,31);
  write_fe(2,1,255,31);
  write_fe(2,2,255,31);
  write_fe(2,3,255,31);
  write_fe(3,1,255,31);
  write_fe(3,2,255,31);
  write_fe(3,3,255,31);
  write_fe(4,1,255,31);
  write_fe(4,2,255,31);
  write_fe(4,3,255,31);
  write_fe(5,3,255,31);

  wait(25,SC_NS);
  release_fe(1,1);
  release_fe(1,2);
  release_fe(1,3);
  release_fe(2,1);
  release_fe(2,2);
  release_fe(2,3);
  release_fe(3,1);
  release_fe(3,2);
  release_fe(3,3);
  release_fe(4,1);
  release_fe(4,2);
  release_fe(4,3);
  release_fe(5,3);

  return;
}

// *****************************************************************************
void data_concentrator_tb::print_output() {

  while(1) {
    wait();
    log_buffer << sc_time_stamp() << ": " << dc_output.read() << std::endl;
  }
}

// *****************************************************************************
void data_concentrator_tb::release_fe(
    const unsigned int fe_chip,
    const unsigned int hit_nr) {

  fe_signals[fe_chip][hit_nr].dv->write(false);

  return;
}
