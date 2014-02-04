/*!
 * @file front_end_chip_tb.cpp
 * @author Christian Amstutz
 * @date Feb 4, 2014
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
    stub_input_sig("stub_input") {

  // ----- Creation and binding of signals -------------------------------------
  dut_front_end_chip.clk(LHC_clock);
  dut_front_end_chip.en(en_sig);
  dut_front_end_chip.stub_input(stub_input_sig);

  for(unsigned int i = 0; i < MAX_HITS_PER_FE_CHIP; i++) {
    std::ostringstream port_name_dv, port_name_data;
    port_name_dv << "hit" << i+1 << "_dv";
    fe_out_signals[i].dv = new sc_signal<bool>(port_name_dv.str().c_str());
    port_name_data << "hit" << i+1 << "_data";
    fe_out_signals[i].data = new sc_signal<stub>(port_name_data.str().c_str());

    dut_front_end_chip.hit_outputs[i].dv->bind( *(fe_out_signals[i].dv) );
    dut_front_end_chip.hit_outputs[i].data->bind( *(fe_out_signals[i].data) );
  }

  // ----- Process registration ------------------------------------------------

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

    log_buffer << std::endl
               << "Simulation Output of Front End Chip TB:" << std::endl
               << "*******************************************" << std::endl;

  return;
}

// *****************************************************************************
void front_end_chip_tb::end_of_elaboration() {
  SC_THREAD(generate_stubs);
  SC_THREAD(analyse_FE_data);
    for(fe_signal_t test_signal : fe_out_signals) {
      sensitive << *test_signal.dv;
    }
  SC_THREAD(analyse_FE_dv);
    for(fe_signal_t test_signal : fe_out_signals) {
      sensitive << *test_signal.dv;
    }

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
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

  wait(32, SC_NS);
  stim_stub.setAddress(100);
  stim_stub.setBend(2);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
  stim_stub.setAddress(120);
  stim_stub.setBend(3);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

  wait(1, SC_NS);
  stim_stub.setAddress(101);
  stim_stub.setBend(4);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
  wait(1, SC_NS);
  stim_stub.setAddress(101);
  stim_stub.setBend(5);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

  wait(25, SC_NS);
  stim_stub.setAddress(1);
  stim_stub.setBend(6);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

  wait(25, SC_NS);
  stim_stub.setAddress(12);
  stim_stub.setBend(7);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
  stim_stub.setAddress(13);
  stim_stub.setBend(8);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

  //! todo: there is an error here with this event falling on a clock edge and does not show on the output
  wait(16, SC_NS);
  stim_stub.setAddress(14);
  stim_stub.setBend(9);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
  wait(1, SC_NS);
  stim_stub.setAddress(1);
  stim_stub.setBend(1);
  stub_input_sig.write(stim_stub);
  log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

  return;
}

// *****************************************************************************
void front_end_chip_tb::analyse_FE_data() {

  while(1) {
    wait();

    unsigned int out_cnt = 0;
    for(fe_signal_t &act_sig : fe_out_signals) {
      out_cnt++;
      if(act_sig.dv->read() == true) {
        stub act_stub = act_sig.data->read();
        log_buffer << sc_time_stamp() <<" Hit" << out_cnt << ": "
                   << std::hex
                   << " Address: 0x" << act_stub.getAddress()
                   << " Bend: 0x" << act_stub.getBend()
                   << std::endl;
      }
    }
  }

}

// *****************************************************************************
void front_end_chip_tb::analyse_FE_dv() {

  while(1) {
    wait();
    log_buffer << sc_time_stamp() << ": DV ";
    for(fe_signal_t test_signal : fe_out_signals) {
      log_buffer << test_signal.dv->read();
      log_buffer << "-";
    }
    log_buffer << std::endl;
  }

}
