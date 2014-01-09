/*!
 * @file SensorModule.cpp
 * @author Christian Amstutz
 * @date Dec 10, 2013
 *
 * @brief
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#include "SensorModule.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class SensorModule
 *
 * The module is sensitive to ....
 */

SensorModule::SensorModule(sc_module_name _name) :
    sc_module(_name),
    dataConcentrator("DC") {

  // ----- Process registration ------------------------------------------------
  //SC_THREAD();
  //  sensitive << clk;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------
  dataConcentrator.clk(clk);
  for(int fe=0; fe<NR_FRONTENDCHIP_PER_MODULE; fe++) {
    //TODO: dataConcentrator.data_input(frontEndChip[fe]->data_output);
  }
  dataConcentrator.data_output(data_output);

  return;
}

