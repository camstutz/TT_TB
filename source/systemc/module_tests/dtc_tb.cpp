/*!
 * @file dtc_tb.cpp
 * @author Christian Amstutz
 * @date August 28, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class dtc_tb
 * The module is sensitive to ...
 */

dtc_tb::dtc_tb(sc_module_name _name,
        track_trigger_config configuration) :
        sc_module(_name),
        gbt_input_links(configuration.dtcs[0].sensor_modules, "gbt_input_link"),
        tower_output_stream("tower_output_stream"),
        LHC_clock("LHC_clock", configuration.LHC_clock_period, SC_NS, 0.5, 25, SC_NS, true),
        dut_dtc("DUT_DTC", configuration.dtcs[0]),
        dut_configuration(configuration.dtcs[0])
{
    // ----- Creation and binding of signals -----------------------------------
    dut_dtc.clk.bind(LHC_clock);
    dut_dtc.gbt_inputs.bind(gbt_input_links);
    dut_dtc.tower_output.bind(tower_output_stream);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_packets);
    SC_THREAD(print_output);
        sensitive << tower_output_stream;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of DTC input unit TB:" << std::endl
            << "***************************************" << std::endl;

    return;
}

// *****************************************************************************
dtc_tb::~dtc_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void dtc_tb::generate_packets()
{
    wait(50, SC_NS);

    CIC_frame input_frame1(dut_configuration.input_unit.CBC_input_stub);
    CIC_frame input_frame2(dut_configuration.input_unit.CBC_input_stub);
    stub stub1(dut_configuration.input_unit.CBC_input_stub, 0, 1, 1, 1, 1, 0);
    input_frame1.add_stub(stub1);
    stub stub2(dut_configuration.input_unit.CBC_input_stub, 0, 1, 1, 1, 2, 0);
    input_frame2 = input_frame1;
    input_frame1.add_stub(stub2);
    gbt_link_format input_packet(input_frame1, input_frame2);

    std::cout << input_packet << std::endl;

    gbt_input_links[sensor_module_address(0,0,0)].write(input_packet);

    wait(580, SC_NS);

    gbt_input_links[sensor_module_address(0,0,0)].write(input_packet);

    wait(500, SC_NS);

    return;
}

// *****************************************************************************
void dtc_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << sc_time_stamp();
         log_buffer << ": " << std::endl;
         log_buffer << tower_output_stream;
         log_buffer << std::endl << std::endl;
    }

}
