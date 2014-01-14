/*!
 * @file sensor_module.cpp
 * @author Christian Amstutz
 * @date Jan 13, 2014
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
    dataConcentrator("DC"),
    clk("clk"),
    data_output("data_output") {

  // ----- Process registration ------------------------------------------------
  //SC_THREAD();
  //  sensitive << clk;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  stub_inputs.resize(NR_FRONTENDCHIP_PER_MODULE);
  for(int fe_nr=0; fe_nr<NR_FRONTENDCHIP_PER_MODULE; fe_nr++) {

    // creating and naming the hit inputs
    sc_in<stub> *stub_port;
    std::ostringstream port_name;
    port_name << "stub_input" << fe_nr;
    stub_port = new sc_in<stub>(port_name.str().c_str());
    stub_inputs[fe_nr] = stub_port;

    // creating, naming and binding the front end chips
    std::ostringstream front_end_name;
    front_end_name << "FrontEnd" << fe_nr;
    front_end_chips[fe_nr] = new front_end_chip(front_end_name.str().c_str());
    front_end_chips[fe_nr]->stub_input(*stub_inputs[fe_nr]);
    //TODO: dataConcentrator.data_input(front_end_chips[fe_nr]->data_output);
  }

  dataConcentrator.clk(clk);
  dataConcentrator.data_output(data_output);

  return;
}

