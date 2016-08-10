/*!
 * @file am_board.cpp
 * @author Christian Amstutz
 * @date August 4, 2016
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

am_board::am_board(const sc_module_name _name, const am_board_config configuration) :
        sc_module(_name),
        layer_nr(configuration.layer_nr),
        clk("clk"),
        frame_inputs(layer_nr, "frame_inputs"),
        hit_output(layer_nr, "hit_output"),
        track_finder_in_signal(layer_nr, "track_finder_in_signal"),
        AM_InputModule("AM_input_module", configuration.input_module),
        TrackFinder("track_finder", configuration.track_finder)
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

// *****************************************************************************
void am_board::set_pattern_bank(pattern_bank* pat_bank)
{
    TrackFinder.set_pattern_bank(pat_bank);

    return;
}

// *****************************************************************************
void am_board::set_module_address_lookup(module_address_lookup* address_lu)
{
    AM_InputModule.set_module_address_lookup(address_lu);

    return;
}
