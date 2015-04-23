/*!
 * @file am_input_module.hpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "am_input_module_one_layer.hpp"
#include "am_input_module_ctrl.hpp"
#include "../track_finder/track_finder.hpp"
#include "../../../../data_formats/prbf/PRBF.hpp"
#include "../../../../systems/TT_configuration.hpp"

#include "../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

#include <map>
#include <vector>

/*!
 * @brief SystemC
 */
class am_input_module : public sc_module
{
public:
    static const unsigned int layer_nr;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<PRBF_2> > frame_inputs;
    sc_map_linear<sc_out<track_finder::hit_stream> > stub_stream_outputs;

    // ----- Local Channel Declarations ----------------------------------------
    sc_buffer<bool> init_processing_sig;
    sc_buffer<bool> delete_frame_sig;
    sc_map_linear<sc_signal<bool> > frame_available_sigs;
    sc_map_linear<sc_signal<bool> > frame_empty_sigs;
    sc_map_linear<sc_signal<bool> > frame_processing_sigs;

    // ----- Process Declarations ----------------------------------------------
    void read_frames();
    void create_stream();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    am_input_module_ctrl controller;
    sc_map_linear<am_input_module_one_layer> input_modules;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    am_input_module(const sc_module_name _name);
};
