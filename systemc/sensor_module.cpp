/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date Feb 6, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "sensor_module.hpp"

// *****************************************************************************

/*!
 * @class sensor_module
 *
 * The module is sensitive to ....
 */

sensor_module::sensor_module(const sc_module_name _name) :
    sc_module(_name),
    clk("clk"),
    dc_out("dc_out"),
    true_sig("true"),
    dataConcentrator("DC") {

  // ----- Module / Port / Signal - creation and naming ------------------------
  unsigned int fe_cnt = 0;
  for (front_end_chip* &fe_chip: front_end_chips) {
    std::ostringstream module_name;
    module_name << "fe_chip" << fe_cnt;
    fe_chip = new front_end_chip(module_name.str().c_str());
    fe_cnt++;
  }

  unsigned int in_cnt = 0;
  for (stub_in_t* &stub_in : stub_inputs) {
    std::ostringstream port_name;
    port_name << "stub_in" << in_cnt;
    stub_in = new sc_fifo_in<stub>(port_name.str().c_str());
    in_cnt++;
  }

  unsigned int fe_sig_cnt = 0;
  for (fe_signal_t &fe_sig : fe_out_signals) {
    unsigned int hit_cnt = 0;
    for (hit_signal_t &hit_sig : fe_sig) {
      std::ostringstream sig_name_dv, sig_name_data;
      sig_name_dv << "fe" << fe_sig_cnt << "_out_dv" << hit_cnt;
      hit_sig.dv = new sc_signal<bool>(sig_name_dv.str().c_str());
      sig_name_data << "fe" << fe_sig_cnt << "_out_data" << hit_cnt;
      hit_sig.data = new sc_signal<stub>(sig_name_data.str().c_str());
      hit_cnt++;
    }
    fe_sig_cnt++;
  }

  // ----- Process registration ------------------------------------------------

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  fe_cnt = 0;
  for (front_end_chip* &fe_chip: front_end_chips) {
    fe_chip->clk(clk);
    //! todo: use the enable port
    fe_chip->en(true_sig);
    fe_chip->stub_input(*stub_inputs[fe_cnt]);
    unsigned int hit_cnt = 0;
    for (front_end_chip::hit_out_t &hit_output : fe_chip->hit_outputs) {
      hit_output.dv->bind(*fe_out_signals[fe_cnt][hit_cnt].dv);
      hit_output.data->bind(*fe_out_signals[fe_cnt][hit_cnt].data);
      hit_cnt++;
    }
    fe_cnt++;
  }

  dataConcentrator.clk(clk);
  dataConcentrator.rst(true_sig);
  fe_cnt = 0;
  for (data_concentrator::fe_port_t &fe_port: dataConcentrator.fe_stub_in) {
    unsigned int hit_cnt = 0;
    for(data_concentrator::fe_in_t &fe_input : fe_port) {
      fe_input.dv->bind(*fe_out_signals[fe_cnt][hit_cnt].dv);
      fe_input.data->bind(*fe_out_signals[fe_cnt][hit_cnt].data);
      hit_cnt++;
    }
    fe_cnt++;
  }
  dataConcentrator.dc_out(dc_out);

  true_sig.write(true);

  return;
}

