/*!
 * @file TT_TB_top.cpp
 * @author Christian Amstutz
 * @date Jan 13, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include <systemc.h>
#include <iostream>
#include <string>
#include <sstream>

#include "TT_configuration.hpp"

#include "sensor_module.hpp"
#include "data_organizer.hpp"
#include "hit_generator.hpp"

int sc_main(int argc, char *agv[]) {

  // ----- Channel declarations ------------------------------------------------
  sc_clock LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true);

  // ----- Variable declarations -----------------------------------------------

  // ----- Module instance declarations ----------------------------------------

  hit_generator hitGenerator("Hit_Generator", "hits.txt");
  //! TODO: change sensorModule array to std::vector and use iterators for the loops
  sensor_module *sensorModule[NR_DETECTOR_LAYERS][NR_DETECTOR_PHI][NR_DETECTOR_Z];

  sensorModule[0][0][0] = new sensor_module("sensor_module");
  sensorModule[0][0][0]->clk(LHC_clock);
  //std::cout << (*hitGenerator.hit_outputs[0][0][0][0]).name() << std::endl;
  //sensorModule[0][0][0]->stub_inputs[0]->bind(*hitGenerator.hit_outputs[0][0][0][0]);
  //sc_signal<stub> test;

  //hitGenerator.hit_outputs[0][0][0][0]->bind(test);
  //sensorModule[0][0][0]->stub_inputs[0]->bind(test);

//  for(int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
//    for(int phi=0; phi<NR_DETECTOR_PHI; phi++) {
//      for(int z=0; z<NR_DETECTOR_Z; z++) {
//        std::ostringstream moduleName;
//        moduleName << "SensorModule_L" << layer << "P" << phi << "Z" << z;
//        sensorModule[layer][phi][z] = new sensor_module(moduleName.str().c_str());
//      }
//    }
//  }
//  data_organizer<NR_SENSOR_MODULES> dataOrganizer("Data_Organizer");

  // ----- Module port binding -------------------------------------------------

  //! TODO: use iterators here
//  for(unsigned int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
//    for(unsigned int phi=0; phi<NR_DETECTOR_PHI; phi++) {
//      for(unsigned int z=0; z<NR_DETECTOR_Z; z++) {
//        sensorModule[layer][phi][z]->clk(LHC_clock);
//        for(unsigned int n=0; n<NR_FRONTENDCHIP_PER_MODULE; n++) {
//          (*sensorModule[layer][phi][z]->stub_inputs[n])(*hitGenerator.hit_outputs[layer][phi][z][n]);
//        }
//      }
//    }
//  }
//  dataOrganizer.clk(LHC_clock);


  // Binding: Sensor Modules --> Data Organizer
//  for(int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
//    for(int phi=0; phi<NR_DETECTOR_PHI; phi++) {
//      for(int z=0; z<NR_DETECTOR_Z; z++) {
//        int linkNumber = layer * NR_DETECTOR_PHI * NR_DETECTOR_Z +
//                         phi * NR_DETECTOR_Z +
//                         z;
//        std::cout << "linknumber: " << linkNumber << std::endl;
//        sensorModule[layer][phi][z]->data_output(moduleLinks[linkNumber]);
//        dataOrganizer.sensorInputs[linkNumber](moduleLinks[linkNumber]);
//      }
//    }
//  }

  // ----- Time unit / resolution setup ----------------------------------------

  // ----- Set up tracing ------------------------------------------------------

  // ----- Start simulation ----------------------------------------------------

  #ifdef DEBUG
  std::cout << "Start simulation ..." << std::endl;
  #endif
  sc_start();
  #ifdef DEBUG
  std::cout << "Simulation ended." << std::endl;
  #endif
  
  return 0;
}
