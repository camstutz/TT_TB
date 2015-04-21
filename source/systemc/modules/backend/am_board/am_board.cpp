/*!
 * @file am_board.cpp
 * @author Christian Amstutz
 * @date February 19, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_board.hpp"

// *****************************************************************************

const unsigned int am_board::layer_nr = NR_DETECTOR_LAYERS;

// *****************************************************************************

/*!
 * @class am_lane
 */

am_board::am_board(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        frame_inputs(NR_DETECTOR_LAYERS, "frame_inputs"),
        hit_output(NR_DETECTOR_LAYERS, "hit_output"),
        track_finder_in_signal(NR_DETECTOR_LAYERS, "track_finder_in_signal"),
        AM_InputModule("AM_input_module"),
        TrackFinder("track_finder")
{
    // ----- Module instance / channel binding ---------------------------------
    AM_InputModule.clk.bind(clk);
    AM_InputModule.frame_inputs.bind(frame_inputs);
    AM_InputModule.stub_stream_outputs.bind(track_finder_in_signal);

    TrackFinder.clk.bind(clk);
    TrackFinder.hit_input.bind(track_finder_in_signal);
    TrackFinder.hit_output.bind(hit_output);

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    return;
}
