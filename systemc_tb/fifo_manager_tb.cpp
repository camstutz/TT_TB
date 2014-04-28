/*!
 * @file fifo_manager_tb.cpp
 * @author Christian Amstutz
 * @date Apr 28, 2014
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
    do_out_data stub;

    wait(25, SC_NS);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,1));
    stub_inputs.at(0,0).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,2));
    stub_inputs.at(0,1).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,3));
    stub_inputs.at(0,2).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,4));
    stub_inputs.at(0,3).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,5));
    stub_inputs.at(0,4).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,6));
    stub_inputs.at(0,5).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,7));
    stub_inputs.at(0,6).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,8));
    stub_inputs.at(0,7).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,9));
    stub_inputs.at(0,8).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,10));
    stub_inputs.at(0,9).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,11));
    stub_inputs.at(0,10).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(0,0,1,12));
    stub_inputs.at(0,11).write(stub);

    wait(100, SC_NS);
    stub = do_out_data(false, do_out_data::do_stub_t(0,0,0,0));
    stub_inputs.write_all(stub);

    wait(100, SC_NS);
    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,1));
    stub_inputs.at(0,0).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,2));
    stub_inputs.at(0,1).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,3));
    stub_inputs.at(0,2).write(stub);
    stub = do_out_data(true, do_out_data::do_stub_t(1,1,0,4));
    stub_inputs.at(0,3).write(stub);

    wait(100, SC_NS);
    stub = do_out_data(false, do_out_data::do_stub_t(0,0,0,0));
    stub_inputs.write_all(stub);

    wait(100, SC_NS);
    stub = do_out_data(true, do_out_data::do_stub_t(2,2,0,20));
    stub_inputs.at(0,0).write(stub);

    wait(100, SC_NS);
    stub = do_out_data(false, do_out_data::do_stub_t(0,0,0,0));
    stub_inputs.write_all(stub);

    return;
}

// *****************************************************************************
void fifo_manager_tb::print_output()
{
    while(1)
    {
         wait();

         for (auto& single_out : fifo_outputs)
         {
             fm_out_data value = single_out.read();
             if (value.get_data_valid_flag())
             {
                 auto out_key = fifo_outputs.get_key(single_out);
                 auto lane = out_key.second.Y_dim;
                 auto layer = out_key.second.X_dim;

                 if (value.get_time_stamp_flag() == true)
                 {
                     log_buffer << sc_time_stamp() << "(" << lane << "," << layer << "):";
                     log_buffer << " TS=" << value.get_data_time_stamp() << std::endl;
                 }
                 else
                 {
                     log_buffer << sc_time_stamp() << "(" << lane << "," << layer << "):";
                     log_buffer << value.get_data_stub() << std::endl;
                 }
             }
         }
    }

}
