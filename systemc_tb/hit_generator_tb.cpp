/*!
 * @file hit_generator_tb.cpp
 * @author Christian Amstutz
 * @date Jan 15, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_generator_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class hit_generator_tb
 * The module is sensitive to ...
 */

hit_generator_tb::hit_generator_tb(sc_module_name _name) :
    sc_module(_name),
    dut_hit_generator("Hit_Generator_DUT", "test_hits.txt") {

  // ----- Creation and binding of signals -------------------------------------
  hit_signals.resize(NR_DETECTOR_LAYERS);
  for(unsigned int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
    hit_signals[layer].resize(NR_DETECTOR_PHI);
    for(unsigned int phi=0; phi<NR_DETECTOR_PHI; phi++) {
      hit_signals[layer][phi].resize(NR_DETECTOR_Z);
      for(unsigned int z=0; z<NR_DETECTOR_Z; z++) {
        hit_signals[layer][phi][z].resize(NR_FRONTENDCHIP_PER_MODULE);
        for(unsigned int fe=0; fe<NR_FRONTENDCHIP_PER_MODULE; fe++) {
          sc_fifo<stub> *hit_signal;
          std::ostringstream signal_name;
          signal_name << "hit_signal_L" << layer << "P" << phi << "Z" << z << "F" << fe;
          hit_signal = new sc_fifo<stub>(signal_name.str().c_str(), MAX_NR_HITS_PER_FE);
          hit_signals[layer][phi][z][fe] = hit_signal;
          dut_hit_generator.hit_outputs[layer][phi][z][fe]->bind(*hit_signals[layer][phi][z][fe]);
        }
      }
    }
  }

  // ----- Process registration ------------------------------------------------
  SC_THREAD(check_output);
  for(unsigned int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
    for(unsigned int phi=0; phi<NR_DETECTOR_PHI; phi++) {
      for(unsigned int z=0; z<NR_DETECTOR_Z; z++) {
        for(unsigned int fe=0; fe<NR_FRONTENDCHIP_PER_MODULE; fe++) {
          sensitive << hit_signals[layer][phi][z][fe]->data_written_event();
        }
      }
    }
  }

  // ----- Module variable initialization --------------------------------------

  // ----- Module instance / channel binding -----------------------------------

  log_buffer << std::endl
             << "Simulation Output of Hit Generator TB:" << std::endl
             << "*******************************************" << std::endl;

  return;
}

// *****************************************************************************
hit_generator_tb::~hit_generator_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void hit_generator_tb::check_output() {

  while(1) {
    wait();
    for(unsigned int layer=0; layer<NR_DETECTOR_LAYERS; layer++) {
      for(unsigned int phi=0; phi<NR_DETECTOR_PHI; phi++) {
        for(unsigned int z=0; z<NR_DETECTOR_Z; z++) {
          for(unsigned int fe=0; fe<NR_FRONTENDCHIP_PER_MODULE; fe++) {
            stub read_stub;
            while (hit_signals[layer][phi][z][fe]->nb_read(read_stub) ) {
              log_buffer << sc_time_stamp () << " @ hit_generator."
                         << "L" << layer
                         << "P" << phi
                         << "Z" << z
                         << "FE" << fe
                         << " : " << std::hex
                         << "0x" << read_stub.getAddress() << " - "
                         << "0x" << read_stub.getBend() << std::endl;
            }
          }
        }
      }
    }
  }

  return;
}
