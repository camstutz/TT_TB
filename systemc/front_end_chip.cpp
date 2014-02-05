/*!
 * @file front_end_chip.cpp
 * @author Christian Amstutz
 * @date Feb 4, 2014
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

front_end_chip::front_end_chip(const sc_module_name _name)
    : sc_module(_name),
      clk("clk"),
      en("en"),
      stub_input("stub_in"),
      selected_stubs("sel_stubs", MAX_HITS_PER_FE_CHIP) {

  // ----- Process registration ------------------------------------------------

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  // Create and name the hit output ports
  unsigned int out_cnt = 1;
  for(hit_out_t& output : hit_outputs) {
    std::ostringstream port_name_dv, port_name_data;
    port_name_dv << "hit" << out_cnt << "_dv";
    output.dv = new sc_out<bool>(port_name_dv.str().c_str());
    port_name_data << "hit" << out_cnt << "_data";
    output.data = new sc_out<stub>(port_name_data.str().c_str());

    out_cnt++;
  }

  return;
}

// *****************************************************************************
void front_end_chip::end_of_elaboration() {

  SC_THREAD(prioritize_hits);
    sensitive << stub_input.data_written_event();
  SC_THREAD(write_hits);
    sensitive << selected_stubs.data_written_event();
}

// *****************************************************************************
void front_end_chip::prioritize_hits() {

  while(1) {
    wait();
    if(!clk.posedge()) {
      wait(clk.posedge_event());
    }

    stub act_stub;
    for(int i=0;
        i <= std::min(stub_input.num_available(), MAX_HITS_PER_FE_CHIP);
        i++) {
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

    unsigned int num_stubs = selected_stubs.num_available();
    for (unsigned int i=0; i<num_stubs; i++) {
      hit_outputs[i].dv->write(true);
      hit_outputs[i].data->write(selected_stubs.read());
    }

    wait(clk.posedge_event());

    for(hit_out_t& output : hit_outputs) {
      output.dv->write(false);
    }
  }

}
