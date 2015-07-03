/*!
 * @file po_layer_splitter_tb.cpp
 * @author Christian Amstutz
 * @date July 1, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "po_layer_splitter_tb.hpp"

// *****************************************************************************
po_layer_splitter_tb::po_layer_splitter_tb(sc_module_name _name,
        po_layer_splitter_config configuration) :
        sc_module(_name),
        stub_input_sig("stub_input_sig"),
        stub_output_sigs(configuration.layer_nr, "stub_output_sig"),
        dut_po_layer_splitter("DUT_po_layer_splitter", configuration)
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stubs);
    SC_THREAD(print_output);
        sc_map_linear<sc_fifo<element_t> >::iterator output_it = stub_output_sigs.begin();
        for (; output_it != stub_output_sigs.end(); ++output_it)
        {
            sensitive << output_it->data_written_event();
        }

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_po_layer_splitter.input_stubs.bind(stub_input_sig);
    dut_po_layer_splitter.splitted_stubs.bind(stub_output_sigs);

    log_buffer << std::endl
            << "Simulation Output of PO layer splitter TB:" << std::endl
            << "******************************************" << std::endl;

    return;
}

// *****************************************************************************
po_layer_splitter_tb::~po_layer_splitter_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void po_layer_splitter_tb::write_stubs()
{
    element_t stub_element;
    element_t::stub_t stub;

    wait(40, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(2, 1, 2, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(2, 1, 2, 1, 1, 1, 3, 1);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    wait(100, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(5, 1, 9, 1, 1, 1, 4);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    wait(500, SC_NS);

    return;
}

// *****************************************************************************
void po_layer_splitter_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;

         unsigned int output_id = 0;
         sc_map_linear<sc_fifo<element_t> >::iterator stub_output_it = stub_output_sigs.begin();
         for (; stub_output_it != stub_output_sigs.end(); ++stub_output_it)
         {
             while (stub_output_it->num_available() > 0)
             {
                 log_buffer << "output " << output_id << ": ";
                 log_buffer << stub_output_it->read() << std::endl;
             }
             ++output_id;
         }

         log_buffer << std::endl;
    }

}
