/*!
 * @file am_chip_read_ctrl.cpp
 * @author Christian Amstutz
 * @date October 14, 2015
 *
 * @brief File contains the implementation of the AM board FSM.
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_chip_read_ctrl.hpp"

// *****************************************************************************

const am_chip_read_ctrl::fsm_states am_chip_read_ctrl::IDLE = 0x01;
const am_chip_read_ctrl::fsm_states am_chip_read_ctrl::START = 0x02;
const am_chip_read_ctrl::fsm_states am_chip_read_ctrl::TX_ROAD = 0x03;

// *****************************************************************************

/*!
 * @class am_chip_write_ctrl
 *
 */

am_chip_read_ctrl::am_chip_read_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        roads_detected("roads_detected"),
        road_input("road_input"),
        road_output("road_output")
{
    // ----- Process registration ----------------------------------------------
    SC_METHOD(controller);
        sensitive << roads_detected << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void am_chip_read_ctrl::controller()
{
    switch (current_state)
    {
    case IDLE:
        if (roads_detected.event() && (roads_detected.read() == true))
        {
            road_output.write(road_stream::IDLE);
            current_state = START;
        }
        break;

    case START:
        road_output.write(road_stream::START_WORD);
        current_state = TX_ROAD;

        SYSTEMC_LOG << road_input.num_available() << " roads detected";

        break;

    case TX_ROAD:
        if (road_input.num_available() > 0)
        {
            road_t value = road_input.read();
            road_output.write(value);
        }
        else
        {
            road_output.write(road_stream::IDLE);
            current_state = IDLE;
        }
        break;

    default:
        current_state = IDLE;
    }

    return;
}
