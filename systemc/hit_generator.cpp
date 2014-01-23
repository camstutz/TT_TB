/*!
 * @file hit_generator.cpp
 * @author Christian Amstutz
 * @date Jan 23, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

// *****************************************************************************

#include "hit_generator.hpp"

// *****************************************************************************

/*!
 * @class hit_generator
 *
 * The module is sensitive to ....
 */

hit_generator::hit_generator(sc_module_name _name , std::string hitFileName)
    : sc_module(_name) {

  // ----- Process registration ------------------------------------------------
  SC_THREAD(schedule_hits);
  //  sensitive << event_in << clk;

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  // Name the hit output ports
  hit_outputs.resize(NR_DETECTOR_LAYERS);
  for(unsigned int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
    hit_outputs[layer].resize(NR_DETECTOR_PHI);
    for(unsigned int phi=0; phi<NR_DETECTOR_PHI; phi++) {
      hit_outputs[layer][phi].resize(NR_DETECTOR_Z);
      for(unsigned int z=0; z<NR_DETECTOR_Z; z++) {
        hit_outputs[layer][phi][z].resize(NR_FRONTENDCHIP_PER_MODULE);
        for(unsigned int fe=0; fe<NR_FRONTENDCHIP_PER_MODULE; fe++) {
          sc_fifo_out<stub> *hit_port;
          std::ostringstream port_name;
          port_name << "hit_outputL" << layer << "P" << phi << "Z" << z << "F" << fe;
          hit_port = new sc_fifo_out<stub>(port_name.str().c_str());
          hit_outputs[layer][phi][z][fe] = hit_port;
        }
      }
    }
  }

  readFile(hitFileName);

  return;
}

// *****************************************************************************
void hit_generator::schedule_hits() {

  while(!hit_queue.empty()) {
    sc_time wait_time;
    HitEvent hit;
    stub processed_stub;

    hit = hit_queue.front();
    hit_queue.pop();

    wait_time = (hit.timeStamp * sc_time(250, SC_NS)) - sc_time_stamp();
    wait(wait_time);

    processed_stub.setAddress(hit.stubAddress);
    processed_stub.setBend(hit.stubBend);
    (*hit_outputs[hit.layer-1][hit.phiCoordinate-1][hit.zCoordinate-1][hit.frontEndChipNr-1])->write(processed_stub);

    #ifdef DEBUG
    std::cout << std::hex << sc_time_stamp() << " hit_generator @ " <<
                             "L" << hit.layer <<
                             "P" << hit.phiCoordinate <<
                             "Z" << hit.zCoordinate <<
                             "FE" <<hit.frontEndChipNr <<
                             " Stub --> 0x" <<
                             processed_stub.getAddress() << "/0x" <<
                             processed_stub.getBend()
                             << std::endl;
    #endif
  }

  return;
}

// *****************************************************************************

int hit_generator::readFile(const std::string &hit_file) {

  std::ifstream hitFile;

  hitFile.open(hit_file.c_str());
  if (hitFile.is_open()) {

    #ifdef DEBUG
    std::cout << "File: " << hit_file << " opened ..." << std::endl;
    #endif

    std::string fileLine;
    HitEvent hit;
    // clear the event queue
    std::queue<HitEvent> empty;
    std::swap(hit_queue, empty);
    while (std::getline(hitFile, fileLine)) {
      std::stringstream fileLineStream(fileLine);
      fileLineStream >> std::hex >> hit.timeStamp >>
                                    hit.layer >>
                                    hit.phiCoordinate >>
                                    hit.zCoordinate >>
                                    hit.frontEndChipNr >>
                                    hit.stubAddress >>
                                    hit.stubBend;
      //! Assumption hits are in the correct order in the file.
      hit_queue.push(hit);

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
    std::cout << "File: " << hit_file << " closed." << std::endl;
    #endif
  }
  else {
    std::cout << "File with hits could not be read: " << hit_file << std::endl;
    return 1;
    // @todo Add exception handling in case file cannot be opened
  }

  return 0;
}
