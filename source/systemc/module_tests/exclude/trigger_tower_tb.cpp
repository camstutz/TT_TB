/*!
 * @file trigger_tower_tb.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower_tb.hpp"

// *****************************************************************************

// *****************************************************************************

trigger_tower_tb::trigger_tower_tb(sc_module_name _name) :
        sc_module(_name),
        stream_in(NR_DETECTOR_LAYERS, "stream_in"),
        neighbour_dv_in(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS, "neighbour_dv_in"),
        neighbour_stub_in(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS, "neighbour_stub_in"),
        neighbour_dv_out(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS, "neighbour_dv_out"),
        neighbour_stub_out(NR_NEIGHBOURING_TOWERS, NR_DETECTOR_LAYERS, "neighbour_stub_out"),
        road_write_en(NR_AM_BOARDS, "road_write_en"),
        road_output(NR_AM_BOARDS, "road_output"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_trigger_tower("trigger_tower", 0, 0)
{
    // ----- Creation and binding of signals -----------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_stream);
        sensitive << LHC_clock.posedge_event();
    SC_THREAD(print_output);
        //do_output.make_sensitive(sensitive);

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
	dut_trigger_tower.clk.bind(LHC_clock);
	dut_trigger_tower.neighbour_dv_in.bind(neighbour_dv_in);
	dut_trigger_tower.neighbour_stub_in.bind(neighbour_stub_in);
	dut_trigger_tower.neighbour_dv_out.bind(neighbour_dv_out);
	dut_trigger_tower.neighbour_stub_out.bind(neighbour_stub_out);
	dut_trigger_tower.road_write_en.bind(road_write_en);
	dut_trigger_tower.road_output.bind(road_output);


  log_buffer << std::endl
             << "Simulation Output of Trigger Tower TB:" << std::endl
             << "***************************************" << std::endl;

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
    return;
}

// *****************************************************************************
void trigger_tower_tb::print_output()
{
    while(1)
    {
        wait();
    }

}
