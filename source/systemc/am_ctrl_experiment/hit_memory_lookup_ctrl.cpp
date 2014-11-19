/*!
 * @file hit_memory_lookup_ctrl.cpp
 * @author Christian Amstutz
 * @date November 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_memory_lookup_ctrl.hpp"

// *****************************************************************************

const hit_memory_lookup_ctrl::fsm_states hit_memory_lookup_ctrl::IDLE = 0x01;
const hit_memory_lookup_ctrl::fsm_states hit_memory_lookup_ctrl::RX_HIT = 0x02;

// *****************************************************************************

/*!
 * @class hit_memory_read_ctrl
 *
 */

hit_memory_lookup_ctrl::hit_memory_lookup_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        superstrip_inputs(LAYER_NUMBER, "superstrip_inputs"),
        lookup_superstrips(LAYER_NUMBER, "lookup_superstrips"),
        event_end("event_end"),
        current_state("current_state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        superstrip_inputs.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void hit_memory_lookup_ctrl::controller()
{
    while (1)
    {
        wait();

        bool wait_flag;
        unsigned int finished_layers;
        switch (current_state)
        {
        case IDLE:
            wait_flag = false;
            for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
            {
                if (superstrip_inputs[layer].read() != START_EVENT)
                {
                    wait_flag = true;
                }
            }
            if (!wait_flag)
            {
                current_state.write(RX_HIT);
                std::cout << sc_time_stamp() << " event detected" << std::endl;
            }
            break;

        case RX_HIT:
            finished_layers = 0;
            for (unsigned int layer = 0; layer < LAYER_NUMBER; ++layer)
            {
                if (superstrip_inputs[layer].read() != IDLE_EVENT)
                {
                    lookup_superstrips[layer].write(superstrip_inputs[layer].read());
                }
                else
                {
                    ++finished_layers;
                }
            }

            if (finished_layers == LAYER_NUMBER)
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
