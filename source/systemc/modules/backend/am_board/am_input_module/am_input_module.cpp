/*!
 * @file am_input_module.cpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_input_module.hpp"

// *****************************************************************************
am_input_module::am_input_module(const sc_module_name _name,
        const am_input_module_config configuration) :
        sc_module(_name),
        layer_nr(configuration.layer_nr),
        clk("clk"),
        frame_inputs(layer_nr, "frame_input"),
        stub_stream_outputs(layer_nr, "stream_output"),
        init_processing_sig("init_processing_sig"),
        delete_frame_sig("delete_frame_sig"),
        frame_available_sigs(layer_nr, "frame_available_sig"),
        frame_empty_sigs(layer_nr, "frame_empty_sig"),
        frame_processing_sigs(layer_nr, "frame_processing_sig"),
        controller("controller", configuration.controller),
        input_modules(layer_nr, "input_modules")
{
    // ----- Module instance / channel binding ---------------------------------
    controller.clk.bind(clk);
    controller.frame_available.bind(frame_available_sigs);
    controller.frame_empty.bind(frame_empty_sigs);
    controller.frame_processing.bind(frame_processing_sigs);
    controller.init_processing.bind(init_processing_sig);
    controller.delete_frame.bind(delete_frame_sig);

    sc_map_linear<sc_in<PRBF_2> >::iterator frame_input_it = frame_inputs.begin();
    sc_map_linear<sc_out<track_finder::hit_stream> >::iterator stub_stream_output_it = stub_stream_outputs.begin();
    sc_map_linear<sc_signal<bool> >::iterator frame_available_sig_it = frame_available_sigs.begin();
    sc_map_linear<sc_signal<bool> >::iterator frame_empty_sig_it = frame_empty_sigs.begin();
    sc_map_linear<sc_signal<bool> >::iterator frame_processing_sig_it = frame_processing_sigs.begin();
    sc_map_linear<am_input_module_one_layer>::iterator input_modules_it = input_modules.begin();
    for (; input_modules_it != input_modules.end(); )
    {
        input_modules_it->clk.bind(clk);
        input_modules_it->start_process_frame.bind(init_processing_sig);
        input_modules_it->delete_frame.bind(delete_frame_sig);
        input_modules_it->frame_input.bind(*frame_input_it);
        input_modules_it->frame_available.bind(*frame_available_sig_it);
        input_modules_it->frame_empty.bind(*frame_empty_sig_it);
        input_modules_it->frame_processing.bind(*frame_processing_sig_it);
        input_modules_it->stub_stream_output.bind(*stub_stream_output_it);

        ++frame_input_it;
        ++stub_stream_output_it;
        ++frame_available_sig_it;
        ++frame_empty_sig_it;
        ++frame_processing_sig_it;
        ++input_modules_it;
    }

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    return;
}

// *****************************************************************************
void am_input_module::set_module_address_lookup(module_address_lookup* address_lu)
{
    sc_map_linear<am_input_module_one_layer>::iterator input_modules_it = input_modules.begin();
    for (; input_modules_it != input_modules.end(); ++input_modules_it)
    {
        input_modules_it->set_address_lookup(address_lu);
    }

    return;
}
