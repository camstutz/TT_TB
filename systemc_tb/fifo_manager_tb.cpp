/*!
 * @file fifo_manager_tb.cpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class fifo_manager_tb
 * The module is sensitive to ...
 */

fifo_manager_tb::fifo_manager_tb(sc_module_name _name) :
        sc_module(_name),
        rst("rst"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_fifo_manager("FIFO_Manager_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_fifo_manager.clk(LHC_clock);
    dut_fifo_manager.rst(rst);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_input);
    SC_THREAD(print_output);
//        sensitive << dc_output;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of FIFO Manager TB:" << std::endl
            << "*******************************************" << std::endl;

    return;
}

// *****************************************************************************
fifo_manager_tb::~fifo_manager_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void fifo_manager_tb::generate_input()
{
    wait(50, SC_NS);

    return;
}

// *****************************************************************************
void fifo_manager_tb::print_output()
{
    while(1)
    {
         wait();
         log_buffer << sc_time_stamp() << ": " << std::endl;
    }
}
