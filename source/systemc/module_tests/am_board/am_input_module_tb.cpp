/*!
 * @file am_input_module_tb.cpp
 * @author Christian Amstutz
 * @date April 21, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_input_module_tb.hpp"

// *****************************************************************************

// *****************************************************************************
am_input_module_tb::am_input_module_tb(sc_module_name _name) :
        sc_module(_name),
        frame_in_sigs(am_input_module::layer_nr, "frame_in_sig"),
        output_streams(am_input_module::layer_nr, "output_stream"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_am_input_module_tb("DUT_AM_input_module")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frames);
    SC_THREAD(print_stream);
        output_streams.make_sensitive(sensitive);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_am_input_module_tb.clk.bind(LHC_clock);
    dut_am_input_module_tb.frame_inputs.bind(frame_in_sigs);
    dut_am_input_module_tb.stub_stream_outputs.bind(output_streams);

    log_buffer << std::endl
            << "Simulation Output of AM input module TB:" << std::endl
            << "****************************************" << std::endl;

    return;
}

// *****************************************************************************
am_input_module_tb::~am_input_module_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void am_input_module_tb::write_frames()
{

    am_input_module_one_layer::frame_t data_frame[6];
    am_input_module_one_layer::frame_t::stub_element_t stub_element;
    am_input_module_one_layer::frame_t::stub_t stub;

    wait(50, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 0, 1);
    stub_element.set_stub(stub);
    data_frame[0].add_stub(stub_element);
    frame_in_sigs[0].write(data_frame[0]);

    for(unsigned int layer = 1; layer < 6; ++layer)
    {
        data_frame[layer] = data_frame[layer-1];
        data_frame[layer].set_bunch_crossing(8);
        stub.set(1, 1, 1, 1, 1, layer, 1);
        stub_element.set_stub(stub);
        data_frame[layer].add_stub(stub_element);

        frame_in_sigs[layer].write(data_frame[layer]);
    }

    wait(50, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(2, 1, 1, 1, 1, 0, 1);
    stub_element.set_stub(stub);
    data_frame[0].add_stub(stub_element);
    frame_in_sigs[0].write(data_frame[0]);

    for(unsigned int layer = 1; layer < 6; ++layer)
    {
        data_frame[layer] = data_frame[layer-1];
        data_frame[layer].set_bunch_crossing(8);
        stub.set(2, 1, 1, 1, 1, layer, 1);
        stub_element.set_stub(stub);
        data_frame[layer].add_stub(stub_element);

        frame_in_sigs[layer].write(data_frame[layer]);
    }

    wait(400, SC_NS);

   return;
}

// *****************************************************************************
void am_input_module_tb::print_stream()
{
    while(1)
    {
         wait();

         unsigned int layer = 0;
         sc_map_linear<sc_buffer<track_finder::hit_stream> >::iterator out_it = output_streams.begin();
         for(; out_it != output_streams.end(); ++out_it)
         {
             if (out_it->event())
             {
                 log_buffer << sc_time_stamp() << " - " << layer << ": ";
                 log_buffer << out_it->read() << std::endl;
             }

             ++layer;
         }
    }

}
