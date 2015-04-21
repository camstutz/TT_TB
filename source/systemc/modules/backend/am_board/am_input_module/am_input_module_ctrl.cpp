/*!
 * @file am_input_module_ctrl.cpp
 * @author Christian Amstutz
 * @date April 20, 2014
 *
 * @brief File contains the implementation of the AM board FSM.
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_input_module_ctrl.hpp"

// *****************************************************************************

const am_input_module_ctrl::fsm_states am_input_module_ctrl::IDLE = 0x01;
const am_input_module_ctrl::fsm_states am_input_module_ctrl::INIT = 0x02;
const am_input_module_ctrl::fsm_states am_input_module_ctrl::PROCESS1 = 0x03;
const am_input_module_ctrl::fsm_states am_input_module_ctrl::PROCESSING = 0x04;

// *****************************************************************************

/*!
 * @class am_input_module_ctrl
 *
 */

am_input_module_ctrl::am_input_module_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        frame_available(NR_DETECTOR_LAYERS, "frame_available"),
        frame_processing(NR_DETECTOR_LAYERS, "frame_processing"),
        init_processing("init_processing")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        sensitive << clk.pos();
        frame_available.make_sensitive(sensitive);
        frame_processing.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void am_input_module_ctrl::controller()
{
    current_state = IDLE;

    while (1)
    {
        wait();

        bool frames_ready = true;
        bool all_frames = true;
        sc_map_linear<sc_in<bool> >::iterator input_it = frame_available.begin();

        switch (current_state)
        {
        case IDLE:
            init_processing.write(false);

            frames_ready = true;
            input_it = frame_available.begin();
            for (; input_it != frame_available.end(); ++input_it)
            {
                frames_ready &= input_it->read();
            }

            if (frames_ready)
            {
                init_processing.write(true);
                current_state = INIT;
            }
            break;

        case INIT:
            init_processing.write(false);
            current_state = PROCESS1;

            break;

        case PROCESS1:
            if (clk.posedge())
            {
                current_state = PROCESSING;
            }

            break;

        case PROCESSING:
            all_frames = false;
            input_it = frame_processing.begin();
            for (; input_it != frame_processing.end(); ++input_it)
            {
                all_frames |= input_it->read();
            }

            if (all_frames == false)
            {
                current_state = IDLE;
            }

            break;

        default:
            current_state = IDLE;
        }
    }
}
