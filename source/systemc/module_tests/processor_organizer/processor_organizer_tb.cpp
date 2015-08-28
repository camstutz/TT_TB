/*!
 * @file processor_organizer_tb.cpp
 * @author Christian Amstutz
 * @date July 3, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "processor_organizer_tb.hpp"

// *****************************************************************************

// *****************************************************************************
processor_organizer_tb::processor_organizer_tb(sc_module_name _name,
        track_trigger_config configuration) :
        sc_module(_name),
        do_input_sigs(configuration.trigger_tower.processor_organizer.do_input_nr, "do_input_sig"),
        processor_output_sigs(configuration.trigger_tower.processor_organizer.processor_output_nr, configuration.trigger_tower.processor_organizer.layer_nr, "processor_output_sig"),
        LHC_clock("LHC_clock", configuration.LHC_clock_period, SC_NS, 0.5, 25, SC_NS, true),
        dut_processor_organizer("DUT_processor_organizer", configuration.trigger_tower.processor_organizer)
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frames);
    SC_THREAD(print_output);
        sensitive << processor_output_sigs;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_processor_organizer.clk.bind(LHC_clock);
    dut_processor_organizer.do_inputs.bind(do_input_sigs);
    dut_processor_organizer.processor_outputs.bind(processor_output_sigs);

    log_buffer << std::endl
            << "Simulation Output of processor organizer TB:" << std::endl
            << "********************************************" << std::endl;

    return;
}

// *****************************************************************************
processor_organizer_tb::~processor_organizer_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void processor_organizer_tb::write_frames()
{

    processor_organizer::po_input_collector::input_frame_t data_frame(4);
    processor_organizer::po_input_collector::input_frame_t::stub_element_t stub_element;
    processor_organizer::po_input_collector::input_frame_t::stub_t stub;

    wait(50, SC_NS);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_MPA);
    stub.set(1, 1, 1, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 2, 1, 1, 1, 1, 3);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    do_input_sigs[0].write(data_frame);

    wait(500, SC_NS);

    do_input_sigs[1].write(data_frame);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 3, 1, 1, 1, 1, 4);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    data_frame.set_bunch_crossing(7);
    do_input_sigs[0].write(data_frame);

    return;
}

// *****************************************************************************
void processor_organizer_tb::print_output()
{
    while(1)
    {
         // wait for 'processor_output_sigs' changes
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;

         for (unsigned int output_id = 0; output_id < dut_processor_organizer.processor_output_nr; ++output_id)
         {
             for (unsigned int layer_id = 0; layer_id < dut_processor_organizer.layer_nr; ++layer_id)
             {
                 if (processor_output_sigs.at(output_id, layer_id).event())
                 {
                     log_buffer << "output " << output_id << ",";
                     log_buffer << "layer " << layer_id << ": " << std::endl;
                     log_buffer << processor_output_sigs.at(output_id, layer_id).read();
                     log_buffer << std::endl;
                 }
             }
         }

         log_buffer << std::endl;
    }

}
