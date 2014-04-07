/*!
 * @file am_board_tb.cpp
 * @author Christian Amstutz
 * @date Apr 7, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_board_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class am_boardm_tb
 * The module is sensitive to ...
 */

am_board_tb::am_board_tb(sc_module_name _name) :
        sc_module(_name),
        reset("reset"),
        init_event("init_event"),
        write_en(NR_DETECTOR_LAYERS, "write_enable"),
        patterns(NR_DETECTOR_LAYERS, "pattern"),
        ready_to_process("ready_to_process"),
        road_ready("road_ready"),
        road("road"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        DUT("am_board_TB")
{
    // ----- Creation and binding of signals -----------------------------------
    reset.write(false);

    DUT.clk(LHC_clock);
    DUT.rst(reset);
    DUT.init_ev(init_event);
    DUT.write_en.bind(write_en);
    DUT.pattern_inputs.bind(patterns);
    DUT.ready_to_process(ready_to_process);
    DUT.data_ready(road_ready);
    DUT.road_output(road);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(create_input);
        sensitive << LHC_clock.posedge_event();
    SC_THREAD(print_output);
        sensitive << road_ready << road;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of AM board TB:" << std::endl
            << "***************************************" << std::endl;

  return;
}

// *****************************************************************************

am_board_tb::~am_board_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void am_board_tb::create_input()
{
    wait(50, SC_NS);
    patterns[0] = 1;
    write_en[0] = true;

    wait(25, SC_NS);
    patterns[0] = 1;
    write_en[0] = false;

    return;
}

// *****************************************************************************
void am_board_tb::print_output()
{
    while(1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": " << road_ready << " - " << road << std::endl;
    }

}
