/*!
 * @file read_ctrl_fsm.cpp
 * @author Christian Amstutz
 * @date February 17, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "read_ctrl_fsm.hpp"

// *****************************************************************************

const read_ctrl_fsm::fsm_states read_ctrl_fsm::IDLE = 0x01;
const read_ctrl_fsm::fsm_states read_ctrl_fsm::PROCESS = 0x02;

// *****************************************************************************

/*!
 * @class read_ctrl_fsm
 *
 * The module is sensitive ...
 */

read_ctrl_fsm::read_ctrl_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        layers_active(NR_DETECTOR_LAYERS, "layers_active"),
        event_active("event_active"),
        current_state("current_state"),
        next_state("next_state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(combinatorial);
        sensitive << current_state;
        layers_active.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;
    next_state = IDLE;

    active_layer_array = 0;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void read_ctrl_fsm::state_logic()
{
    while (1)
    {
        wait();

        current_state.write(next_state.read());
    }

}

// *****************************************************************************
void read_ctrl_fsm::combinatorial()
{
    while (1)
    {
        wait();

        unsigned int id = 0;
        sc_map_linear<sc_in<bool> >::iterator layer_active_it = layers_active.begin();

        switch (current_state)
        {
        case IDLE:
            id = 0;
            layer_active_it = layers_active.begin();
            for (; layer_active_it != layers_active.end(); ++layer_active_it)
            {
                active_layer_array[id] = layer_active_it->read();
                ++id;
            }

            if (active_layer_array.to_uint() != 0)
            {
                event_active.write(true);
                next_state = PROCESS;
            }
            else
            {
                event_active.write(false);
                next_state = IDLE;
            }
            break;

        case PROCESS:
            id = 0;
            layer_active_it = layers_active.begin();
            for (; layer_active_it != layers_active.end(); ++layer_active_it)
            {
                if (layer_active_it->read() == false)
                active_layer_array[id] = false;
                ++id;
            }

            if (active_layer_array != 0)
            {
                event_active.write(true);
                next_state = PROCESS;
            }
            else
            {
                event_active.write(false);
                next_state = IDLE;
            }
            break;

        default:
            next_state = IDLE;
        }
    }
}
