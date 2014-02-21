/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date Feb 20, 2014
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
        stub_inputs (NR_FE_CHIP_PER_MODULE, "stub_in"),
        dc_out("dc_out"),
        fe_out_signals (MAX_HITS_PER_FE_CHIP, "fe_out_sig"),
        true_sig("true"),
        front_end_chips(NR_FE_CHIP_PER_MODULE, "front_end_chip"),
        dataConcentrator("DC")
{
    // ----- Module / Port / Signal - creation and naming ------------------------

    // ----- Process registration ------------------------------------------------

    // ----- Module variable initialization --------------------------------------

    // ----- Module instance / channel binding -----------------------------------

  unsigned int fe_cnt = 0;
  for (auto& fe_chip: front_end_chips) {
    fe_chip.clk(clk);
    //! todo: use the enable port
    fe_chip.en(true_sig);
    fe_chip.stub_input(*stub_inputs[fe_cnt]);
//    unsigned int hit_cnt = 0;
//    for (front_end_chip::hit_out_t &hit_output : fe_chip->hit_outputs) {
//      hit_output.dv->bind(*fe_out_signals[fe_cnt][hit_cnt].dv);
//      hit_output.data->bind(*fe_out_signals[fe_cnt][hit_cnt].data);
//      hit_cnt++;
//    }
    fe_cnt++;
  }

    dataConcentrator.clk(clk);
    dataConcentrator.rst(true_sig);
    dataConcentrator.fe_stub_in.bind(fe_out_signals);

//* todo: remove when bind in previous line works
//    fe_cnt = 0;
//  for (data_concentrator::fe_port_t &fe_port: dataConcentrator.fe_stub_in) {
//    unsigned int hit_cnt = 0;
//    for(data_concentrator::fe_in_t &fe_input : fe_port) {
//      fe_input.dv->bind(*fe_out_signals[fe_cnt][hit_cnt].dv);
//      fe_input.data->bind(*fe_out_signals[fe_cnt][hit_cnt].data);
//      hit_cnt++;
//    }
//    fe_cnt++;

  dataConcentrator.dc_out(dc_out);

  true_sig.write(true);

  return;
}

