/*!
 * @file am_board.hpp
 * @author Christian Amstutz
 * @date April 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "am_input_module/am_input_module.hpp"
#include "track_finder/track_finder.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"
#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

/*!
 * @brief SystemC
 */
class am_board : public sc_module
{
public:
    typedef PRBF_2 input_t;
    typedef track_finder::hit_stream output_stream_t;

    static const unsigned int layer_nr;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;

    sc_map_linear<sc_in<input_t> > frame_inputs;

    sc_map_linear<sc_out<output_stream_t> > hit_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<track_finder::hit_stream> > track_finder_in_signal;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    am_input_module AM_InputModule;
    track_finder TrackFinder;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_board(const sc_module_name _name);
};
