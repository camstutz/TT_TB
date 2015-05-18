/*!
 * @file am_chip_tb.cpp
 * @author Christian Amstutz
 * @date April 23, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_chip_tb.hpp"

// *****************************************************************************

// *****************************************************************************
am_chip_tb::am_chip_tb(sc_module_name _name) :
        sc_module(_name),
        hit_input_sigs(am_chip::layer_nr, "hit_input_sig"),
        road_output_sig("road_output_sig"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        patterns(am_chip::layer_nr),
        dut_AM_chip("DUT_AM_chip", &patterns)
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_streams);
    SC_THREAD(print_output);
        sensitive << road_output_sig;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_AM_chip.clk.bind(LHC_clock);
    dut_AM_chip.hit_inputs.bind(hit_input_sigs);
    dut_AM_chip.road_output.bind(road_output_sig);

    patterns.generate_patterns_straight(100);

    log_buffer << std::endl
            << "Simulation Output of AM chip TB:" << std::endl
            << "********************************" << std::endl;

    return;
}

// *****************************************************************************
am_chip_tb::~am_chip_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void am_chip_tb::write_streams()
{
    hit_input_sigs.write(am_chip::superstrip_stream::IDLE);

    wait(50, SC_NS);
    hit_input_sigs.write(am_chip::superstrip_stream::START_WORD);

    wait(25, SC_NS);
    hit_input_sigs.write(4);

    wait(25, SC_NS);
    hit_input_sigs.write(am_chip::superstrip_stream::IDLE);

    return;
}

// *****************************************************************************
void am_chip_tb::print_output()
{
    while(1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": ";
        log_buffer << road_output_sig.read();
        log_buffer << std::endl;
    }

}
