/*!
 * @file trigger_tower_tb.cpp
 * @author Christian Amstutz
 * @date April 21, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower_tb.hpp"

// *****************************************************************************

// *****************************************************************************

trigger_tower_tb::trigger_tower_tb(sc_module_name _name) :
        sc_module(_name),
        dtc_input_sigs(trigger_tower::prb_nr, trigger_tower::dtc_per_prb, "dtc_input_sig"),
        hit_output_sigs(trigger_tower::prb_nr, trigger_tower::AM_boards_per_proc_unit, trigger_tower::detector_layer_nr, "hit_output_sig"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_trigger_tower("trigger_tower")
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stream);
    SC_THREAD(print_output);
        hit_output_sigs.make_sensitive(sensitive);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
	dut_trigger_tower.clk.bind(LHC_clock);
	dut_trigger_tower.dtc_inputs.bind(dtc_input_sigs);
	dut_trigger_tower.hit_outputs.bind(hit_output_sigs);

    log_buffer << std::endl
            << "Simulation Output of Trigger Tower TB:" << std::endl
            << "**************************************" << std::endl;

    return;
}

// *****************************************************************************

trigger_tower_tb::~trigger_tower_tb() {

    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void trigger_tower_tb::write_stream()
{
    data_organizer::do_input_collector::input_frame_t data_frame;
    data_organizer::do_input_collector::input_frame_t::stub_element_t stub_element;
    data_organizer::do_input_collector::input_frame_t::stub_t stub;

    data_frame.set_bunch_crossing(6);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(0, 0, 1, 2, 2, 1);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 0, 1, 2, 2, 2);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    wait(100, SC_NS);

    dtc_input_sigs.at(0, 0).write(data_frame);
    wait(25, SC_NS);

    data_frame.set_bunch_crossing(9);
    dtc_input_sigs.at(1, 0).write(data_frame);

    wait(475, SC_NS);

    data_frame.set_bunch_crossing(20);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(0, 0, 1, 1, 1, 1);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    stub_element.set_type_field(PRBF::element_type::local_CBC);
    stub.set(1, 0, 1, 1, 1, 2);
    stub_element.set_stub(stub);
    data_frame.add_stub(stub_element);

    dtc_input_sigs.at(0, 0).write(data_frame);
    wait(10, SC_NS);
    dtc_input_sigs.at(1, 0).write(data_frame);

    return;
}

// *****************************************************************************
void trigger_tower_tb::print_output()
{
    while(1)
    {
        wait();
        sc_map_cube<sc_buffer<am_board::output_stream_t> >::iterator hit_output_it = hit_output_sigs.begin();
        for(; hit_output_it != hit_output_sigs.end(); ++hit_output_it)
        {
            sc_map_cube<sc_buffer<am_board::output_stream_t> >::full_key_type hit_out_key = hit_output_sigs.get_key(*hit_output_it).second;
            if (hit_output_it->event())
            {
                log_buffer << sc_time_stamp();
                log_buffer << " - ";
                log_buffer << hit_out_key.Z_dim << ",";
                log_buffer << hit_out_key.Y_dim << ",";
                log_buffer << hit_out_key.X_dim;
                log_buffer << ": " << hit_output_it->read();
                log_buffer << std::endl;
            }
        }
    }

}
