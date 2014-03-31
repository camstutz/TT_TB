/*!
 * @file am_system_tb.cpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_system_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class am_system_tb
 * The module is sensitive to ...
 */

am_system_tb::am_system_tb(sc_module_name _name) :
        sc_module(_name),
        reset("reset"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        input_fifos(1, "input_fifo"),
        fifo_fsms(1, "fifo_fsm")
{
    // ----- Creation and binding of signals -----------------------------------
    reset.write(false);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(create_input);
        sensitive << LHC_clock.posedge_event();
    SC_THREAD(print_output);
        //sensitive << do_output[0];

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of AM system TB:" << std::endl
            << "***************************************" << std::endl;

  return;
}

// *****************************************************************************

am_system_tb::~am_system_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void am_system_tb::create_input()
{
    return;
}

// *****************************************************************************
void am_system_tb::print_output()
{
  while(1)
  {
    wait();

    log_buffer << sc_time_stamp() << ": ";
  }

}
