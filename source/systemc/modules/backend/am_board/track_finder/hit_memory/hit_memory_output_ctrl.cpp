/*!
 * @file hit_memory_output_ctrl.cpp
 * @author Christian Amstutz
 * @date December 3, 2014
 *
 * @brief File contains the implementation of the AM board FSM.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_memory_output_ctrl.hpp"

// *****************************************************************************

const hit_memory_output_ctrl::fsm_states hit_memory_output_ctrl::IDLE = 0x01;
const hit_memory_output_ctrl::fsm_states hit_memory_output_ctrl::START = 0x02;
const hit_memory_output_ctrl::fsm_states hit_memory_output_ctrl::TX_ROAD = 0x03;

// *****************************************************************************

/*!
 * @class am_chip_write_ctrl
 *
 */

hit_memory_output_ctrl::hit_memory_output_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        start_transmission("start_transmission"),
        hit_input(LAYER_NUMBER, "hit_input"),
        hit_output(LAYER_NUMBER, "hit_output")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        sensitive << start_transmission << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void hit_memory_output_ctrl::controller()
{
    current_state = IDLE;
    hit_output.write_all(hit_stream::IDLE);

    while (1)
    {
        wait();

        unsigned int finished_layer;
        switch (current_state)
        {
        case IDLE:
            if (start_transmission.event())
            {
                hit_output.write_all(hit_stream::IDLE);
                current_state = START;
            }
            break;

        case START:
            hit_output.write_all(hit_stream::START_WORD);
            current_state = TX_ROAD;
            break;

        case TX_ROAD:
            finished_layer = 0;
            for (unsigned int layer=0; layer < LAYER_NUMBER; ++layer)
            {
                if (hit_input[layer].num_available() > 0)
                {
                    hit_output[layer].write(hit_input[layer].read());
                }
                else
                {
                    hit_output[layer].write(hit_stream::IDLE);
                    ++finished_layer;
                }
            }
            if (finished_layer >= LAYER_NUMBER)
            {
                current_state = IDLE;
            }
            break;

        default:
            current_state = IDLE;
        }
    }
}
