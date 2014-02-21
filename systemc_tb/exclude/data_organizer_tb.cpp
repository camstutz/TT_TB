/*!
 * @file data_organizer_tb.cpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
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
        fe_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP, "fe_signal"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_organizer("Data_Organizer_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_data_organizer.clk(LHC_clock);
    dut_data_organizer.rst(rst);

    dut_data_organizer


//      dut_data_concentrator.fe_stub_in[fe_cnt][hit_cnt].dv->bind(*fe_in_port.dv);
//      dut_data_concentrator.fe_stub_in[fe_cnt][hit_cnt].data->bind(*fe_in_port.data);


  //dut_data_organizer.dc_out(dc_output);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stream);
    SC_THREAD(print_output);
        sensitive << dc_output;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  log_buffer << std::endl
             << "Simulation Output of Data Organizer TB:" << std::endl
             << "***************************************" << std::endl;

  return;
}

// *****************************************************************************
void data_organizer_tb::end_of_elaboration() {

  return;
}

// *****************************************************************************

data_organizer_tb::~data_organizer_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void data_organizer_tb::write_stream() {

  return;
}

// *****************************************************************************
void data_organizer_tb::print_output() {

  while(1) {
    wait();
    log_buffer << sc_time_stamp() << ": " << dc_output.read() << std::endl;
  }
}
