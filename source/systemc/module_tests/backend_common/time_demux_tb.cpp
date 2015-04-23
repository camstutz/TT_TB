/*!
 * @file do_demux_tb.cpp
 * @author Christian Amstutz
 * @date April 16, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "time_demux_tb.hpp"

// *****************************************************************************
time_demux_tb::time_demux_tb(sc_module_name _name) :
        sc_module(_name),
        bunch_crossing_request_sig("bunch_crossing_request_sig"),
        stub_input_sig("stub_input_sig"),
        proc_unit_output_sigs(do_demux::proc_unit_output_nr, do_demux::layer_nr, "proc_unit_output_sigs"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_do_demux("DUT_do_demux", 2, 0)
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stubs);
        sensitive << bunch_crossing_request_sig;
    SC_THREAD(print_output);
        proc_unit_output_sigs.make_sensitive(sensitive);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_do_demux.clk.bind(LHC_clock);
    dut_do_demux.bunch_crossing_request.bind(bunch_crossing_request_sig);
    dut_do_demux.stub_input[0].bind(stub_input_sig);
    dut_do_demux.proc_unit_outputs.bind(proc_unit_output_sigs);

    log_buffer << std::endl
            << "Simulation Output of DO demux TB:" << std::endl
            << "********************************************" << std::endl;

    return;
}

// *****************************************************************************
time_demux_tb::~time_demux_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void time_demux_tb::write_stubs()
{
    do_demux::input_t stub_element;
    do_demux::input_t::stub_t stub;

    while (bunch_crossing_request_sig.read() != 6)
    {
        wait();
    }

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 3, 1);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    while (bunch_crossing_request_sig.read() != 8)
    {
        wait();
    }

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    stub_input_sig.write(stub_element);

    wait(500, SC_NS);

    return;
}

// *****************************************************************************
void time_demux_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;

         unsigned int output_id = 0;
         sc_map_linear<sc_buffer<do_demux::output_t> >::iterator proc_output_it = proc_unit_output_sigs.begin();
         for (; proc_output_it != proc_unit_output_sigs.end(); ++proc_output_it)
         {
             if (proc_output_it->event())
             {
                 log_buffer << "output " << output_id << ":" << std::endl;
                 log_buffer << *proc_output_it;
             }
             ++output_id;
         }

         log_buffer << std::endl;
    }

}
