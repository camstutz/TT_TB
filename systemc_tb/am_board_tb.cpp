/*!
 * @file am_board_tb.cpp
 * @author Christian Amstutz
 * @date Apr 10, 2014
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
        DUT("AM_board_DUT")
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

    write_en[0] = true;
    write_en[1] = true;
    write_en[2] = true;
    write_en[3] = true;
    write_en[4] = true;
    write_en[5] = true;
    patterns[0] = 1;
    patterns[1] = 1;
    patterns[2] = 1;
    patterns[3] = 1;
    patterns[4] = 1;
    patterns[5] = 1;

    wait(25, SC_NS);
    write_en[0] = true;
    write_en[1] = false;
    write_en[2] = false;
    write_en[3] = false;
    write_en[4] = false;
    write_en[5] = true;
    patterns[0] = 2;
    patterns[1] = 0;
    patterns[2] = 0;
    patterns[3] = 0;
    patterns[4] = 0;
    patterns[5] = 8;

    wait(25, SC_NS);
    write_en[0] = true;
    patterns[0] = 3;
    patterns[5] = 0;
    write_en[5] = false;

    wait(25, SC_NS);
    write_en[0] = false;
    patterns[0] = 0;

    wait(300, SC_NS);
    write_en[0] = true;
    write_en[1] = true;
    write_en[2] = true;
    write_en[3] = true;
    write_en[4] = true;
    write_en[5] = true;
    patterns[0] = 6;
    patterns[1] = 6;
    patterns[2] = 5;
    patterns[3] = 5;
    patterns[4] = 5;
    patterns[5] = 5;

    wait(25, SC_NS);
    write_en[0] = true;
    write_en[1] = true;
    write_en[2] = true;
    write_en[3] = true;
    write_en[4] = true;
    write_en[5] = true;
    patterns[0] = 5;
    patterns[1] = 5;
    patterns[2] = 6;
    patterns[3] = 6;
    patterns[4] = 6;
    patterns[5] = 6;

    wait(25, SC_NS);
    write_en[0] = false;
    write_en[1] = false;
    write_en[2] = false;
    write_en[3] = false;
    write_en[4] = false;
    write_en[5] = false;
    patterns[0] = 0;
    patterns[1] = 0;
    patterns[2] = 0;
    patterns[3] = 0;
    patterns[4] = 0;
    patterns[5] = 0;

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
