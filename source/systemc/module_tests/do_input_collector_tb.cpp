/*!
 * @file do_input_collector_tb.cpp
 * @author Christian Amstutz
 * @date April 16, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "do_input_collector_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class do_input_collector_tb
 * The module is sensitive to ...
 */

do_input_collector_tb::do_input_collector_tb(sc_module_name _name) :
        sc_module(_name),
        dtc_input_sig(do_input_collector::dtc_input_nr, "dtc_input_sig"),
        stub_output_fifo("stub_output_fifo"),
        dut_do_input_collector("DUT_do_input_collector")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frames);
    SC_THREAD(print_output);
        sensitive << stub_output_fifo.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_do_input_collector.dtc_inputs.bind(dtc_input_sig);
    dut_do_input_collector.stub_output.bind(stub_output_fifo);


    log_buffer << std::endl
            << "Simulation Output of DO input collector TB:" << std::endl
            << "********************************************" << std::endl;

    return;
}

// *****************************************************************************
do_input_collector_tb::~do_input_collector_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void do_input_collector_tb::write_frames()
{

    do_input_collector::input_frame_t data_frame(4);
    do_input_collector::input_frame_t::stub_element_t stub_element;
    do_input_collector::input_frame_t::stub_t stub;

    wait(50, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 3);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    dtc_input_sig[0].write(data_frame);

    wait(500, SC_NS);

    dtc_input_sig[1].write(data_frame);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 4);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    data_frame.set_bunch_crossing(7);
    dtc_input_sig[0].write(data_frame);



    return;
}

// *****************************************************************************
void do_input_collector_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;
         while (stub_output_fifo.num_available() > 0)
         {
                 log_buffer << stub_output_fifo.read() << std::endl;
         }
         log_buffer << std::endl;
    }

}
