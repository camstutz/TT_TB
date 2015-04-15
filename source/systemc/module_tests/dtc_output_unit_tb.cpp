/*!
 * @file dtc_output_unit_tb.cpp
 * @author Christian Amstutz
 * @date April 14, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_output_unit_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class dtc_output_unit_tb
 * The module is sensitive to ...
 */

dtc_output_unit_tb::dtc_output_unit_tb(sc_module_name _name) :
        sc_module(_name),
        bx_sorted_inputs(NR_DC_WINDOW_CYCLES, "bx_sorted_inputs"),
        tower_output("tower_output"),
        bx_sig("bx_sig"),
        read_buffer_sig("read_buffer_sig"),
        write_buffer_sig("write_buffer_sig"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_dtc_controller("DUT_dtc_controller"),
        dut_dtc_output_unit("DUT_DTC_output_unit")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_dtc_controller.clk.bind(LHC_clock);
    dut_dtc_controller.bunch_crossing.bind(bx_sig);
    dut_dtc_controller.read_buffer.bind(read_buffer_sig);
    dut_dtc_controller.write_buffer.bind(write_buffer_sig);

    dut_dtc_output_unit.clk.bind(LHC_clock);
    dut_dtc_output_unit.bunch_crossing.bind(bx_sig);
    dut_dtc_output_unit.read_buffer.bind(read_buffer_sig);
    dut_dtc_output_unit.write_buffer.bind(write_buffer_sig);
    dut_dtc_output_unit.bx_sorted_stubs.bind(bx_sorted_inputs);
    dut_dtc_output_unit.tower_out_stream.bind(tower_output);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(fill_FIFOs);
    SC_THREAD(print_output);
        sensitive << tower_output;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of DTC output unit TB:" << std::endl
            << "***************************************" << std::endl;

    return;
}

// *****************************************************************************
dtc_output_unit_tb::~dtc_output_unit_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void dtc_output_unit_tb::fill_FIFOs()
{
    dtc_output_unit::input_t stub_element;
    dtc_output_unit::input_t::stub_t stub;

    wait(50, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    bx_sorted_inputs[2].write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    bx_sorted_inputs[2].write(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 3);
    stub_element.set_stub(stub);
    bx_sorted_inputs[3].write(stub_element);

    wait(500, SC_NS);

    return;
}

// *****************************************************************************
void dtc_output_unit_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;
         log_buffer << tower_output.read();
         log_buffer << std::endl;
    }

}
