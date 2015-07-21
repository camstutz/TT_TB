/*!
 * @file am_input_module_one_layer_tb.cpp
 * @author Christian Amstutz
 * @date July 21, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_input_module_one_layer_tb.hpp"

// *****************************************************************************

// *****************************************************************************
am_input_module_one_layer_tb::am_input_module_one_layer_tb(sc_module_name _name) :
        sc_module(_name),
        start_process_frame_sig("start_process_frame_sig"),
        delete_frame_sig("delete_frame_sig"),
        frame_in_sig("frame_in_sig"),
        frame_available_sig("frame_available_sig"),
        frame_empty_sig("frame_empty_sig"),
        frame_processing_sig("frame_processing_sig"),
        output_stream("output_stream"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_am_input_module_one_layer_tb("DUT_AM_input_module_one_layer")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frames);
    SC_THREAD(print_control);
        sensitive << frame_available_sig;
        sensitive << frame_empty_sig;
        sensitive << frame_processing_sig;
    SC_THREAD(print_stream);
        sensitive << output_stream;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_am_input_module_one_layer_tb.clk.bind(LHC_clock);
    dut_am_input_module_one_layer_tb.start_process_frame.bind(start_process_frame_sig);
    dut_am_input_module_one_layer_tb.delete_frame.bind(delete_frame_sig);
    dut_am_input_module_one_layer_tb.frame_input.bind(frame_in_sig);
    dut_am_input_module_one_layer_tb.frame_available.bind(frame_available_sig);
    dut_am_input_module_one_layer_tb.frame_empty.bind(frame_empty_sig);
    dut_am_input_module_one_layer_tb.frame_processing.bind(frame_processing_sig);
    dut_am_input_module_one_layer_tb.stub_stream_output.bind(output_stream);

    log_buffer << std::endl
            << "Simulation Output of AM input module one layer TB:" << std::endl
            << "**************************************************" << std::endl;

    return;
}

// *****************************************************************************
am_input_module_one_layer_tb::~am_input_module_one_layer_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void am_input_module_one_layer_tb::write_frames()
{

    am_input_module_one_layer::frame_t data_frame(4);
    am_input_module_one_layer::frame_t::stub_element_t stub_element;
    am_input_module_one_layer::frame_t::stub_t stub;

    wait(50, SC_NS);
    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    data_frame.set_bunch_crossing(5);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    data_frame.set_bunch_crossing(5);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 2, 1, 1, 1, 1, 3);
    stub_element.set_stub(stub);
    data_frame.set_bunch_crossing(5);
    data_frame.add_stub(stub_element);

    frame_in_sig.write(data_frame);

    wait(100, SC_NS);
    start_process_frame_sig.write(true);

    wait(25, SC_NS);
    start_process_frame_sig.write(false);

    wait(400, SC_NS);
    frame_in_sig.write(data_frame);

    wait(25, SC_NS);
    frame_in_sig.write(data_frame);

    wait(100, SC_NS);
    start_process_frame_sig.write(true);

    wait(25, SC_NS);
    start_process_frame_sig.write(false);

    wait(400, SC_NS);
    delete_frame_sig.write(true);

    wait(25, SC_NS);
    delete_frame_sig.write(false);

    return;
}

// *****************************************************************************
void am_input_module_one_layer_tb::print_control()
{
    while(1)
    {
         wait();

         log_buffer << sc_time_stamp() <<": ";
         log_buffer << "avail=" << frame_available_sig.read() << ", ";
         log_buffer << "empty=" << frame_empty_sig.read() << ", ";
         log_buffer << "processing=" << frame_processing_sig.read();
         log_buffer << " - ready!" << std::endl;
    }

}

// *****************************************************************************
void am_input_module_one_layer_tb::print_stream()
{
    while(1)
    {
         wait();

         log_buffer << sc_time_stamp() << ": ";
         log_buffer << output_stream.read() << std::endl;
    }

}
