/*!
 * @file HitGenerator.cpp
 * @author Christian Amstutz
 * @date Dec 10, 2013
 *
 * @brief
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#include "HitGenerator.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class HitGenerator
 *
 * The module is sensitive to ....
 */

HitGenerator::HitGenerator(sc_module_name _name , std::string hitFileName)
    : sc_module(_name) {

  // ----- Process registration ------------------------------------------------
  //SC_THREAD();
  //  sensitive << event_in << clk;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  std::ifstream hitFile;

  hitFile.open(hitFileName.c_str());
  if (hitFile.is_open()) {
    #ifdef DEBUG
    std::cout << "File: " << hitFileName << " opened ..." << std::endl;
    #endif
    std::string fileLine;
    HitEvent hit;

    while (std::getline(hitFile, fileLine)) {
      std::stringstream fileLineStream(fileLine);
      fileLineStream >> std::hex >> hit.timeStamp >>
                                    hit.layer >>
                                    hit.phiCoordinate >>
                                    hit.zCoordinate >>
                                    hit.frontEndChipNr >>
                                    hit.stubAddress >>
                                    hit.stubBend;

      #ifdef DEBUG
      std::cout << "Hit read -" << std::hex << " TS:0x" << hit.timeStamp <<
                                               ", Lay:0x" << hit.layer <<
                                               ", Phi:0x" << hit.phiCoordinate <<
                                               ", Z:0x" << hit.zCoordinate <<
                                               ", FE:0x" << hit.frontEndChipNr <<
                                               ", Stub:0x" << hit.stubAddress <<
                                               ", Bend:0x" << hit.stubBend <<
                                               std::endl;
      #endif
    }

    hitFile.close();
    #ifdef DEBUG
    std::cout << "File: " << hitFileName << " closed." << std::endl;
    #endif
  }
  else {
    std::cout << "File with hits could not be read: " << hitFileName << std::endl;
    // @todo Add exception handling in case file cannot be opened
  }

  return;
}
