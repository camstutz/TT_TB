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
        stub_inputs(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "stub_input"),
        fifo_outputs(NR_AM_BOARDS, NR_DETECTOR_LAYERS, "fifo_output"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_fifo_manager("FIFO_Manager_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_fifo_manager.clk.bind(LHC_clock);
    dut_fifo_manager.rst.bind(rst);
    dut_fifo_manager.stub_in.bind(stub_inputs);
    dut_fifo_manager.fifo_out.bind(fifo_outputs);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_input);
    SC_THREAD(print_output);
        fifo_outputs.make_sensitive(sensitive);

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

    std::cout << sc_time_stamp() << ": here" << std::endl;

    do_out_data stub = do_out_data(true, do_out_data::do_stub_t(0,0,0,0));
    stub_inputs.at(0,0).write(stub);

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
