/*!
 * @file do_stub_buffer_tb.cpp
 * @author Christian Amstutz
 * @date April 16, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "do_stub_buffer_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class do_stub_buffer_tb
 * The module is sensitive to ...
 */

do_stub_buffer_tb::do_stub_buffer_tb(sc_module_name _name) :
        sc_module(_name),
        stub_input_fifo("stub_input_fifo"),
        bunch_crossing_select_sig("bunch_crossing_select_sig"),
        output_fifo("output_fifo"),
        dut_do_stub_buffer("do_stub_buffer")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stubs);
    SC_THREAD(print_output);
        sensitive << output_fifo.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_do_stub_buffer.stub_input.bind(stub_input_fifo);
    dut_do_stub_buffer.bunch_crossing_select.bind(bunch_crossing_select_sig);
    dut_do_stub_buffer.stub_output.bind(output_fifo);


    log_buffer << std::endl
            << "Simulation Output of DO stub buffer TB:" << std::endl
            << "***************************************" << std::endl;

    return;
}

// *****************************************************************************
do_stub_buffer_tb::~do_stub_buffer_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void do_stub_buffer_tb::write_stubs()
{
    do_stub_buffer::element_t stub_element;
    do_stub_buffer::element_t::stub_t stub;

    wait(50, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    stub_input_fifo.write(do_stub_buffer::input_pair(6, stub_element));

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    stub_input_fifo.write(do_stub_buffer::input_pair(6, stub_element));

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 3);
    stub_element.set_stub(stub);
    stub_input_fifo.write(do_stub_buffer::input_pair(8, stub_element));

    wait(500, SC_NS);

    bunch_crossing_select_sig.write(6);

    wait(100, SC_NS);

    bunch_crossing_select_sig.write(8);

    wait(100, SC_NS);

    bunch_crossing_select_sig.write(6);

    return;
}

// *****************************************************************************
void do_stub_buffer_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;
         while (output_fifo.num_available() > 0)
         {
                 log_buffer <<  bunch_crossing_select_sig << ": ";
                 log_buffer << output_fifo.read() << std::endl;
         }
         log_buffer << std::endl;
    }

}
