/*!
 * @file data_organizer_tb.cpp
 * @author Christian Amstutz
 * @date July 1, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "data_organizer_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class data_organizer_tb
 * The module is sensitive to ...
 */

data_organizer_tb::data_organizer_tb(sc_module_name _name,
        track_trigger_config configuration) :
        sc_module(_name),
        dtc_input_sigs(configuration.trigger_towers[0].data_organizers[0].DTCs.size(), "dtc_input_sig"),
        proc_output_sigs(configuration.trigger_tower.data_organizer.proc_unit_nr, "proc_output_sig"),
        LHC_clock("LHC_clock", configuration.LHC_clock_period, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_organizer("dut_data_organizer", configuration.trigger_towers[0].data_organizers[0])
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frames);
    SC_THREAD(print_output);
        sensitive << proc_output_sigs;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    dut_data_organizer.clk.bind(LHC_clock);
    dut_data_organizer.dtc_inputs.bind(dtc_input_sigs);
    dut_data_organizer.proc_unit_outputs.bind(proc_output_sigs);

    log_buffer << std::endl
            << "Simulation Output of data organizer TB:" << std::endl
            << "***************************************" << std::endl;

    return;
}

// *****************************************************************************
data_organizer_tb::~data_organizer_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void data_organizer_tb::write_frames()
{
    data_organizer::do_input_collector::input_frame_t data_frame(4);
    data_organizer::do_input_collector::input_frame_t::stub_element_t stub_element;
    data_organizer::do_input_collector::input_frame_t::stub_t stub;

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

    dtc_input_sigs[0].write(data_frame);

    wait(500, SC_NS);

    dtc_input_sigs[0].write(data_frame);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 1, 1, 1, 1, 4);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    data_frame.set_bunch_crossing(7);
    dtc_input_sigs[0].write(data_frame);

    return;
}

// *****************************************************************************
void data_organizer_tb::print_output()
{
    while(1)
    {
         wait();

         log_buffer << std::endl;
         log_buffer << sc_time_stamp() <<": " << std::endl;

         unsigned int output_id = 0;
         sc_map_linear<sc_buffer<data_organizer::do_demux::output_t> >::iterator proc_output_it = proc_output_sigs.begin();
         for (; proc_output_it != proc_output_sigs.end(); ++proc_output_it)
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
