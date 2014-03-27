/*!
 * @file hit_generator_tb.cpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
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
        hit_signals(NR_DETECTOR_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z, NR_FE_CHIP_PER_MODULE, "hit_signal"),
        dut_hit_generator("Hit_Generator_DUT", "test_hits.txt")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_hit_generator.hit_outputs.bind(hit_signals);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(check_output);
    for (auto& hit_signal : hit_signals)
    {
        sensitive << hit_signal.data_written_event();
    }
    //hit_signals.make_sensitive(this->sensitive);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
               << "Simulation Output of Hit Generator TB:" << std::endl
               << "*******************************************" << std::endl;

    return;
}

// *****************************************************************************
hit_generator_tb::~hit_generator_tb()
{
   std::cout << log_buffer.str();

   return;
}

// *****************************************************************************
void hit_generator_tb::check_output()
{
  while(1)
  {
      wait();

      for (auto& hit_signal: hit_signals)
      {
          hit_generator::hitgen_stub_t read_stub;
          while (hit_signal.nb_read(read_stub)) {
              std::pair<bool, sc_map_4d<sc_fifo<hit_generator::hitgen_stub_t>>::full_key_type> signal_key;
              signal_key = hit_signals.get_key(hit_signal);
              log_buffer << sc_time_stamp () << " @ hit_generator."
                         << "L" << signal_key.second.W_dim
                         << "P" << signal_key.second.Z_dim
                         << "Z" << signal_key.second.Y_dim
                         << "FE" << signal_key.second.X_dim
                         << " : " << std::hex
                         << "0x" << read_stub.get_strip() << " - "
                         << "0x" << read_stub.get_bend() << std::endl;
          }
      }

  }

  return;
}
