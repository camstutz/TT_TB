/*!
 * @file am_chip_read_ctrl.cpp
 * @author Christian Amstutz
 * @date November 17, 2014
 *
 * @brief File contains the implementation of the AM board FSM.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_chip_read_ctrl.hpp"

// *****************************************************************************

const am_chip_read_ctrl::fsm_states am_chip_read_ctrl::IDLE = 0x01;
const am_chip_read_ctrl::fsm_states am_chip_read_ctrl::RX_HIT = 0x02;

// *****************************************************************************

/*!
 * @class am_chip_read_ctrl
 *
 */

am_chip_read_ctrl::am_chip_read_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        hit_inputs(LAYER_NUMBER, "hit_inputs"),
        process_hits(LAYER_NUMBER, "process_hit"),
        process_roads("process_roads"),
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
void am_chip_read_ctrl::controller()
{
    process_roads.write(false);

    while (1)
    {
        wait();

        bool wait_flag;
        sc_map_linear<sc_in<superstrip_t> >::iterator hit_input_it = hit_inputs.begin();
        sc_map_linear<sc_out<bool> >::iterator process_hit_it = process_hits.begin();
        switch (current_state)
        {
        case IDLE:
            wait_flag = false;
            hit_input_it = hit_inputs.begin();
            for (; hit_input_it != hit_inputs.end(); ++hit_input_it)
            {
                if (hit_input_it->read() != START_EVENT)
                {
                    wait_flag = true;
                }
            }
            if (!wait_flag)
            {
                current_state.write(RX_HIT);
                for (unsigned int i=0; i<LAYER_NUMBER; ++i)
                {
                    process_hits.write_all(true);
                }
            }
            break;

        case RX_HIT:
            hit_input_it = hit_inputs.begin();
            for (unsigned int i=0; hit_input_it != hit_inputs.end(); ++hit_input_it)
            {
                if (hit_input_it->read() == IDLE_EVENT)
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
                process_roads.write(true);
            }

            break;

        default:
            current_state = IDLE;
        }
    }
}
