/*!
 * @file gbt_tb.cpp
 * @author Christian Amstutz
 * @date April 10, 2015
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
        LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true),
        gbt_dut("GBT_CBC_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    gbt_dut.clk.bind(LHC_clock);
    gbt_dut.cic_in.bind(input_streams);
    gbt_dut.optical_link.bind(optical_link);


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

    gbt::input_t test_frame;
    CIC::header frame_header(CIC::header::CBC, CIC::header::status_OK, 8);
    test_frame.set_header(frame_header);

    CIC::stub_CBC stub(0,1,2,1);
    test_frame.add_stub(stub);
    stub = CIC::stub_CBC(0,1,2,2);
    test_frame.add_stub(stub);

    input_streams[0].write(test_frame);

    wait(177, SC_NS);
    stub = CIC::stub_CBC(0,1,2,3);
    test_frame.add_stub(stub);
    input_streams[0].write(test_frame);
    stub = CIC::stub_CBC(0,1,2,4);
    test_frame.add_stub(stub);
    input_streams[1].write(test_frame);

    wait(1000, SC_NS);

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
