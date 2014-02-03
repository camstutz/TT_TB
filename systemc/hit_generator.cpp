/*!
 * @file hit_generator.cpp
 * @author Christian Amstutz
 * @date Feb 3, 2014
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
 */

hit_generator::hit_generator(sc_module_name _name , std::string hitFileName)
    : sc_module(_name) {

  // ----- Process registration ------------------------------------------------
  SC_THREAD(schedule_hits);

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  // Name the hit output ports
  unsigned int layer_cnt=0;
  hit_outputs.resize(NR_DETECTOR_LAYERS);
  for(layer_dim_out_t& layer : hit_outputs) {
    layer_cnt++;
    layer.resize(NR_DETECTOR_PHI);
    unsigned int phi_cnt=0;
    for(phi_dim_out_t& phi : layer) {
      phi_cnt++;
      phi.resize(NR_DETECTOR_Z);
      unsigned int z_cnt=0;
      for(z_dim_out_t& z : phi) {
        z_cnt++;
        z.resize(NR_FE_CHIP_PER_MODULE);
        unsigned int fe_cnt=0;
        for(hit_out_t& hit_port : z) {
          fe_cnt++;
          std::ostringstream port_name;
          port_name << "hit_output" << "L" << layer_cnt
                                    << "P" << phi_cnt
                                    << "Z" << z_cnt
                                    << "F" << fe_cnt;
          hit_port = new sc_fifo_out<stub>(port_name.str().c_str());
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

    wait_time = (hit.timeStamp * sc_time(LHC_CLOCK_PREIOD_NS, SC_NS));
    wait_time = wait_time - sc_time_stamp();
    wait(wait_time);

    //! todo: check vor validity of data and adapt to given range if possible

    processed_stub.setAddress(hit.stubAddress);
    processed_stub.setBend(hit.stubBend);
    hit_out_t act_hit = hit_outputs[hit.layer-1]
                                   [hit.phiCoordinate-1]
                                   [hit.zCoordinate-1]
                                   [hit.frontEndChipNr-1];
    act_hit->write(processed_stub);

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

  //! todo: check that input file fits to detector architecture

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
      fileLineStream >> std::hex >> hit.timeStamp
                                 >> hit.layer
                                 >> hit.phiCoordinate
                                 >> hit.zCoordinate
                                 >> hit.frontEndChipNr
                                 >> hit.stubAddress
                                 >> hit.stubBend;

      //! Assumption hits are in the correct order in the file.
      hit_queue.push(hit);

      #ifdef DEBUG
      std::cout << "Hit read -" << std::hex << " TS:0x" << hit.timeStamp
                                            << ", Lay:0x" << hit.layer
                                            << ", Phi:0x" << hit.phiCoordinate
                                            << ", Z:0x" << hit.zCoordinate
                                            << ", FE:0x" << hit.frontEndChipNr
                                            << ", Stub:0x" << hit.stubAddress
                                            << ", Bend:0x" << hit.stubBend
                                            << std::endl;
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
