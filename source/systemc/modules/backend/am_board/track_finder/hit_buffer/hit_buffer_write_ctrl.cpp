/*!
 * @file hit_buffer_read_ctrl.cpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_buffer_write_ctrl.hpp"

// *****************************************************************************

const hit_buffer_write_ctrl::fsm_states hit_buffer_write_ctrl::IDLE = 0x01;
const hit_buffer_write_ctrl::fsm_states hit_buffer_write_ctrl::RX_HIT = 0x02;

const unsigned int hit_buffer_write_ctrl::layer_nr = NR_DETECTOR_LAYERS;

// *****************************************************************************

/*!
 * @class hit_buffer_read_ctrl
 *
 */

hit_buffer_write_ctrl::hit_buffer_write_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        hit_inputs(layer_nr, "hit_inputs"),
        process_hits(layer_nr, "process_hit"),
        event_begin("event_begin"),
        event_end("event_end"),
        current_state("current_state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        hit_inputs.make_sensitive(sensitive);
        process_hits.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void hit_buffer_write_ctrl::controller()
{
    while (1)
    {
        wait();

        bool wait_flag;
        sc_map_linear<sc_in<superstrip_stream> >::iterator hit_input_it = hit_inputs.begin();
        sc_map_linear<sc_out<bool> >::iterator process_hit_it = process_hits.begin();
        switch (current_state)
        {
        case IDLE:
            wait_flag = false;
            hit_input_it = hit_inputs.begin();
            for (; hit_input_it != hit_inputs.end(); ++hit_input_it)
            {
                if (hit_input_it->read() != superstrip_stream::START_WORD)
                {
                    wait_flag = true;
                }
            }
            if (!wait_flag)
            {
                current_state.write(RX_HIT);
                for (unsigned int i=0; i<layer_nr; ++i)
                {
                    event_begin.write(true);
                    process_hits.write_all(true);
                }
            }
            break;

        case RX_HIT:
            hit_input_it = hit_inputs.begin();
            for (unsigned int i=0; hit_input_it != hit_inputs.end(); ++hit_input_it)
            {
                if (hit_input_it->read() == superstrip_stream::IDLE)
                {
                    process_hits[i].write(false);
                }
                ++i;
            }

            wait_flag = false;
            process_hit_it = process_hits.begin();
            for (; process_hit_it != process_hits.end(); ++process_hit_it)
            {
                if (process_hit_it->read())
                {
                    wait_flag = true;
                }
            }

            if (!wait_flag)
            {
                current_state.write(IDLE);
                event_end.write(true);
            }

            break;

        default:
            current_state = IDLE;
        }
    }

}
