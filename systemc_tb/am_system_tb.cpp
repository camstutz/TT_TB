/*!
 * @file am_system_tb.cpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_system_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class am_system_tb
 * The module is sensitive to ...
 */

am_system_tb::am_system_tb(sc_module_name _name) :
        sc_module(_name),
        reset("reset"),
        input_stubs(NR_DETECTOR_LAYERS, "input_stub"),
        fifo_not_empty(NR_DETECTOR_LAYERS, "FIFO_not_empty"),
        fifo_read_en(NR_DETECTOR_LAYERS, "FIFO_read_en"),
        fifo_stubs(NR_DETECTOR_LAYERS, "FIFO_stubs"),
        init_event("init_event"),
        am_write_en(NR_DETECTOR_LAYERS, "AM_write_en"),
        am_stubs(NR_DETECTOR_LAYERS, "AM_stub"),
        am_data_ready("AM_data_ready"),
        am_road("AM_road"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        input_fifos(NR_DETECTOR_LAYERS, "input_fifo"),
        am_ctrl("AM_controller"),
        pattern_reco_board("pattern_reco_board")
{
    // ----- Creation and binding of signals -----------------------------------
    reset.write(false);

    unsigned int id = 0;
    for (auto& input_fifo : input_fifos)
    {
        input_fifo.clk.bind(LHC_clock);
        input_fifo.rst.bind(reset);
        input_fifo.read_en.bind(fifo_read_en[id]);
        input_fifo.not_empty.bind(fifo_not_empty[id]);
        input_fifo.stub_in.bind(input_stubs[id]);
        input_fifo.stub_out.bind(fifo_stubs[id]);

        ++id;
    }

    am_ctrl.clk.bind(LHC_clock);
    am_ctrl.init.bind(reset);
    am_ctrl.fifo_not_empty.bind(fifo_not_empty);
    am_ctrl.stub_inputs.bind(fifo_stubs);
    am_ctrl.data_ready.bind(am_data_ready);
    am_ctrl.road_in.bind(am_road);
    am_ctrl.init_ev.bind(init_event);
    am_ctrl.fifo_read_en.bind(fifo_read_en);
    am_ctrl.am_write_en.bind(am_write_en);
    am_ctrl.am_stub_outputs.bind(am_stubs);
    am_ctrl.road_write_en.bind(road_write_en_dead);
    am_ctrl.road_output.bind(output_road);

    pattern_reco_board.clk.bind(LHC_clock);
    pattern_reco_board.rst.bind(reset);
    pattern_reco_board.init_ev.bind(init_event);
    pattern_reco_board.write_en.bind(am_write_en);
    pattern_reco_board.pattern_inputs.bind(am_stubs);
    pattern_reco_board.ready_to_process.bind(ready_to_process_dead);
    pattern_reco_board.data_ready.bind(am_data_ready);
    pattern_reco_board.road_output.bind(am_road);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(create_input);
        sensitive << LHC_clock.posedge_event();
    SC_THREAD(detect_roads);
        sensitive << output_road;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of AM system TB:" << std::endl
            << "***************************************" << std::endl;

  return;
}

// *****************************************************************************

am_system_tb::~am_system_tb() {

  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void am_system_tb::create_input()
{
    wait(100, SC_NS);

    input_stubs[0].write(do_out_data(true, do_out_data::do_stub_t(0,0,0,5)));
    input_stubs[1].write(do_out_data(true, do_out_data::do_stub_t(0,0,0,5)));
    input_stubs[2].write(do_out_data(true, do_out_data::do_stub_t(0,0,0,5)));
    input_stubs[3].write(do_out_data(true, do_out_data::do_stub_t(0,0,0,5)));
    input_stubs[4].write(do_out_data(true, do_out_data::do_stub_t(0,0,0,5)));
    input_stubs[5].write(do_out_data(true, do_out_data::do_stub_t(0,0,0,5)));

    wait(25, SC_NS);
    input_stubs[0].write(do_out_data());
    input_stubs[1].write(do_out_data());
    input_stubs[2].write(do_out_data());
    input_stubs[3].write(do_out_data());
    input_stubs[4].write(do_out_data());
    input_stubs[5].write(do_out_data());

    return;
}

// *****************************************************************************
void am_system_tb::detect_roads()
{
    while(1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": " << output_road << std::endl;
    }

}
