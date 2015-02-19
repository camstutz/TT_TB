/*!
 * @file am_controller.cpp
 * @author Christian Amstutz
 * @date February 19, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_controller.hpp"

// *****************************************************************************

/*!
 * @class am_controller
 */

am_controller::am_controller(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        fifo_not_empty(NR_DETECTOR_LAYERS, "fifo_not_empty"),
        fifo_write_en(NR_DETECTOR_LAYERS, "fifo_write_en"),
        stub_inputs(NR_DETECTOR_LAYERS, "stub_input"),
        fifo_read_en(NR_DETECTOR_LAYERS, "fifo_read_en"),
        stub_outputs(NR_DETECTOR_LAYERS, "stub_output"),
        event_start_sig("event_start_sig"),
        transmission_start_sig("transmission_start_sig"),
        event_active_sig("event_active_sig"),
        fifo_controller_array(NR_DETECTOR_LAYERS, "FIFO_controllers"),
        read_controller("read_controller")
{
    // ----- Module instance / channel binding ---------------------------------
    read_controller.clk.bind(clk);
    read_controller.fifo_not_empty.bind(fifo_not_empty);
    read_controller.fifo_write_en.bind(fifo_write_en);
    read_controller.layers_active.bind(fifo_read_en);
    read_controller.event_start.bind(event_start_sig);
    read_controller.transmission_start.bind(transmission_start_sig);
    read_controller.event_active.bind(event_active_sig);


    unsigned int id = 0;
    sc_map_linear<fifo_ctrl>::iterator fifo_ctrl_it = fifo_controller_array.begin();
    for (; fifo_ctrl_it != fifo_controller_array.end(); ++fifo_ctrl_it)
    {
        fifo_ctrl_it->clk.bind(clk);
        fifo_ctrl_it->event_start.bind(event_start_sig);
        fifo_ctrl_it->transmission_start.bind(transmission_start_sig);
        fifo_ctrl_it->event_active.bind(event_active_sig);
        fifo_ctrl_it->stub_input.bind(stub_inputs[id]);
        fifo_ctrl_it->fifo_read_en.bind(fifo_read_en[id]);
        fifo_ctrl_it->stub_output.bind(stub_outputs[id]);

        ++id;
    }

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    return;
}
