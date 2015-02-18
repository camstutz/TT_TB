/*!
 * @file am_board.cpp
 * @author Christian Amstutz
 * @date February 18, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_board.hpp"

// *****************************************************************************

/*!
 * @class am_lane
 */

am_board::am_board(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        clk_fifo("clk_fifo"),
        fifo_write_en(NR_DETECTOR_LAYERS, "fifo_write_ens"),
        fifo_inputs(NR_DETECTOR_LAYERS, "fifo_inputs"),
        road_write_en("road_write_en"),
        fifo_not_empty_sig(NR_DETECTOR_LAYERS, "fifo_not_empty_sig"),
        fifo_read_en_sig(NR_DETECTOR_LAYERS, "fifo_read_en_sig"),
        fifo_stub_out_sig(NR_DETECTOR_LAYERS, "fifo_stub_out_sig"),
        track_finder_in_signal(NR_DETECTOR_LAYERS, "track_finder_in_signal"),
        track_finder_out_signal(NR_DETECTOR_LAYERS, "track_finder_out_signal"),
        stub_fifo_array(NR_DETECTOR_LAYERS, "stub_fifo"),
        AMcontroller("AM_controller"),
        TrackFinder("track_finder")
{
    // ----- Module instance / channel binding ---------------------------------
    unsigned int layer = 0;
    sc_map_linear<stub_fifo<STUB_FIFO_DEPTH> >::iterator fifo_it = stub_fifo_array.begin();
    for (; fifo_it != stub_fifo_array.end(); ++fifo_it)
    {
        fifo_it->clk_write.bind(clk_fifo);
        fifo_it->clk_read.bind(clk);
        fifo_it->write_en.bind(fifo_write_en[layer]);
        fifo_it->stub_in.bind(fifo_inputs[layer]);
        fifo_it->not_empty.bind(fifo_not_empty_sig[layer]);
        fifo_it->read_en.bind(fifo_read_en_sig[layer]);
        fifo_it->stub_out.bind(fifo_stub_out_sig[layer]);

        ++layer;
    }

    AMcontroller.clk.bind(clk);
    AMcontroller.fifo_not_empty.bind(fifo_not_empty_sig);
    AMcontroller.fifo_write_en.bind(fifo_write_en);
    AMcontroller.fifo_read_en.bind(fifo_read_en_sig);
    AMcontroller.stub_inputs.bind(fifo_stub_out_sig);
    AMcontroller.stub_outputs.bind(track_finder_in_signal);

    TrackFinder.clk.bind(clk);
    TrackFinder.hit_input.bind(track_finder_in_signal);
    TrackFinder.hit_output.bind(track_finder_out_signal);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_result);
        track_finder_out_signal.make_sensitive(sensitive);

    // ----- Module variable initialization ------------------------------------

    return;
}

// *****************************************************************************
void am_board::process_result()
{
    while(1)
    {
        wait();
        std::cout <<  track_finder_out_signal[0].read() << std::endl;
    }
}

