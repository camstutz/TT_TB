/*!
 * @file dtc_input_unit_tb.cpp
 * @author Christian Amstutz
 * @date April 13, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_input_unit_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class dtc_input_unit_tb
 * The module is sensitive to ...
 */

dtc_input_unit_tb::dtc_input_unit_tb(sc_module_name _name) :
        sc_module(_name),
        gbt_input_link("gbt_input_link"),
        bx_sorted_outputs(NR_DC_WINDOW_CYCLES, "bx_sorted_output"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_dtc_input_unit("DUT_DTC_input_unit")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_dtc_input_unit.clk.bind(LHC_clock);
    dut_dtc_input_unit.gbt_input.bind(gbt_input_link);
    dut_dtc_input_unit.bx_sorted_stubs.bind(bx_sorted_outputs);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_packets);
    SC_THREAD(print_output);
        sc_map_linear<sc_fifo<dtc_input_unit::output_t> >::iterator output_it = bx_sorted_outputs.begin();
        for (; output_it != bx_sorted_outputs.end(); ++output_it)
        {
            sensitive << output_it->data_written_event();
        }

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of DTC input unit TB:" << std::endl
            << "***************************************" << std::endl;

    return;
}

// *****************************************************************************
dtc_input_unit_tb::~dtc_input_unit_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void dtc_input_unit_tb::generate_packets()
{
    wait(50, SC_NS);

    CIC_frame input_frame;
    CIC::stub_CBC stub1(1, 1, 1, 1);
    input_frame.add_stub(stub1);
    CIC::stub_CBC stub2(2, 1, 1, 2);
    input_frame.add_stub(stub2);
    gbt_link_format input_packet(input_frame, input_frame);

    std::cout << input_packet << std::endl;

    gbt_input_link.write(input_packet);

    wait(580, SC_NS);

    gbt_input_link.write(input_packet);

    wait(500, SC_NS);

    return;
}

// *****************************************************************************
void dtc_input_unit_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;

         sc_map_linear<sc_fifo<dtc_input_unit::output_t> >::iterator output_it = bx_sorted_outputs.begin();
         for (; output_it != bx_sorted_outputs.end(); ++output_it)
         {
             while (output_it->num_available() > 0)
             {
                 std::pair<bool, typename sc_map_linear<sc_fifo<dtc_input_unit::output_t> >::full_key_type> id;
                 id = bx_sorted_outputs.get_key(*output_it);
                 log_buffer << id.second.X_dim;
                 log_buffer << " -> ";
                 log_buffer << output_it->read() << std::endl;
             }
         }
    }

}
