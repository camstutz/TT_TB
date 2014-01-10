/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date Jan 9, 2014
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

sensor_module::sensor_module(sc_module_name _name) :
    sc_module(_name),
    dataConcentrator("DC") {

  // ----- Process registration ------------------------------------------------
  //SC_THREAD();
  //  sensitive << clk;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------
  dataConcentrator.clk(clk);
  for(int fe=0; fe<NR_FRONTENDCHIP_PER_MODULE; fe++) {
    frontEndChip[fe]->stub_input(stub_input[fe]);
    //TODO: dataConcentrator.data_input(frontEndChip[fe]->data_output);
  }
  dataConcentrator.data_output(data_output);

  return;
}

