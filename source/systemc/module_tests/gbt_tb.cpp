/*!
 * @file gbt_tb.cpp
 * @author Christian Amstutz
 * @date April 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "gbt_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class gbt_tb
 * The module is sensitive to ...
 */

gbt_tb::gbt_tb(sc_module_name _name) :
        sc_module(_name),
        input_streams(2, "input_streams"),
        optical_link("optical_link"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        gbt_cbc_dut("GBT_CBC_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    gbt_cbc_dut.clk.bind(LHC_clock);
    gbt_cbc_dut.cic_in.bind(input_streams);
    gbt_cbc_dut.optical_link.bind(optical_link);


    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_cic_data);
    SC_THREAD(print_output);
        sensitive << optical_link;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of GBT-CBC TB:" << std::endl
            << "**********************************************" << std::endl;

    return;
}

// *****************************************************************************
gbt_tb::~gbt_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void gbt_tb::generate_cic_data()
{
    wait(50, SC_NS);

    input_streams[0].write(gbt_cbc::frame_t());

    return;
}

// *****************************************************************************
void gbt_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;
         log_buffer << optical_link.read() << std::endl;
    }
}
