/*!
 * @file read_ctrl_fsm.cpp
 * @author Christian Amstutz
 * @date February 19, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "read_ctrl_fsm.hpp"

// *****************************************************************************

const read_ctrl_fsm::fsm_states read_ctrl_fsm::IDLE = 0x01;
const read_ctrl_fsm::fsm_states read_ctrl_fsm::INIT_EVENT = 0x02;
const read_ctrl_fsm::fsm_states read_ctrl_fsm::START_TRANS = 0x03;
const read_ctrl_fsm::fsm_states read_ctrl_fsm::PROCESS = 0x04;

// *****************************************************************************

/*!
 * @class read_ctrl_fsm
 *
 * The module is sensitive ...
 */

read_ctrl_fsm::read_ctrl_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        fifo_not_empty(NR_DETECTOR_LAYERS, "fifo_not_empty"),
        fifo_write_en(NR_DETECTOR_LAYERS, "fifo_write_en"),
        layers_active(NR_DETECTOR_LAYERS, "layers_active"),
        event_start("event_start"),
        transmission_start("transmission_start"),
        event_active("event_active"),
        current_state("current_state"),
        next_state("next_state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(combinatorial);
        sensitive << current_state;
        fifo_not_empty.make_sensitive(sensitive);
        fifo_write_en.make_sensitive(sensitive);
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

        bool event_pending = false;
        bool fifo_writing = false;
        unsigned int id = 0;
        sc_map_linear<sc_in<bool> >::iterator fifo_not_empty_it = fifo_not_empty.begin();
        sc_map_linear<sc_in<bool> >::iterator fifo_write_en_it = fifo_write_en.begin();
        sc_map_linear<sc_in<bool> >::iterator layer_active_it = layers_active.begin();

        switch (current_state)
        {
        case IDLE:
            event_active.write(false);
            event_start.write(false);
            transmission_start.write(false);

            fifo_not_empty_it = fifo_not_empty.begin();
            for (; fifo_not_empty_it != fifo_not_empty.end(); ++fifo_not_empty_it)
            {
                if (fifo_not_empty_it->read() == true)
                {
                    event_pending = true;
                }
            }
            fifo_write_en_it = fifo_write_en.begin();
            for (; fifo_write_en_it != fifo_write_en.end(); ++fifo_write_en_it)
            {
                if (fifo_write_en_it->read() == true)
                {
                    fifo_writing = true;
                }
            }

            if ((event_pending == true) & (fifo_writing == false))
            {
                next_state = INIT_EVENT;
            }
            else
            {
                next_state = IDLE;
            }
            break;

        case INIT_EVENT:
            event_active.write(true);
            event_start.write(true);
            transmission_start.write(false);

            next_state = START_TRANS;
            break;

        case START_TRANS:
            event_active.write(true);
            event_start.write(false);
            transmission_start.write(true);

            next_state = PROCESS;
            break;

        case PROCESS:
            event_active.write(true);
            event_start.write(false);
            transmission_start.write(false);

            active_layer_array = 0;
            id = 0;
            layer_active_it = layers_active.begin();
            for (; layer_active_it != layers_active.end(); ++layer_active_it)
            {
                if (layer_active_it->read() == true)
                {
                    active_layer_array[id] = true;
                }
                ++id;
            }

            if (active_layer_array != 0)
            {
                next_state = PROCESS;
            }
            else
            {
                next_state = IDLE;
            }
            break;

        default:
            next_state = IDLE;
        }
    }
}
