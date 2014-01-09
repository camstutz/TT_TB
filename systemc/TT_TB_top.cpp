/*!
 * @file TT_TB_top.cpp
 * @author Christian Amstutz
 * @date Dec 6, 2013
 *
 * @brief
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#include <systemc.h>
#include <iostream>
#include <string>
#include <sstream>

#include "TT_configuration.hpp"

#include "SensorModule.hpp"
#include "DataOrganizer.hpp"
#include "HitGenerator.hpp"

int sc_main(int argc, char *agv[]) {

  // ----- Channel declarations ------------------------------------------------
  sc_clock LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true);
  
  sc_signal<int> moduleLinks[NR_SENSOR_MODULES];

  // ----- Variable declarations -----------------------------------------------

  // ----- Module instance declarations ----------------------------------------

  HitGenerator hitGenerator("Hit_Generator", "../hits.txt");
  SensorModule *sensorModule[NR_DETECTOR_LAYERS][NR_DETECTOR_PHI][NR_DETECTOR_Z];
  for(int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
    for(int phi=0; phi<NR_DETECTOR_PHI; phi++) {
      for(int z=0; z<NR_DETECTOR_Z; z++) {
        std::string moduleName;
        std::stringstream moduleNameStr(moduleName);
        moduleNameStr << "SensorModule_L" << layer << "P" << phi << "Z" << z;
        sensorModule[layer][phi][z] = new SensorModule(moduleName.c_str());
      }
    }
  }
  DataOrganizer<NR_SENSOR_MODULES> dataOrganizer("Data_Organizer");

  // ----- Module port binding -------------------------------------------------
  // Clock distribution
  hitGenerator.clk(LHC_clock);
  for(int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
    for(int phi=0; phi<NR_DETECTOR_PHI; phi++) {
      for(int z=0; z<NR_DETECTOR_Z; z++) {
        sensorModule[layer][phi][z]->clk(LHC_clock);
      }
    }
  }
  dataOrganizer.clk(LHC_clock);


  // Binding: Sensor Modules --> Data Organizer
  for(int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
    for(int phi=0; phi<NR_DETECTOR_PHI; phi++) {
      for(int z=0; z<NR_DETECTOR_Z; z++) {
        int linkNumber = layer * NR_DETECTOR_PHI * NR_DETECTOR_Z +
                         phi * NR_DETECTOR_Z +
                         z;
        std::cout << "linknumber: " << linkNumber << std::endl;
        sensorModule[layer][phi][z]->data_output(moduleLinks[linkNumber]);
        dataOrganizer.sensorInputs[linkNumber](moduleLinks[linkNumber]);
      }
    }
  }

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
