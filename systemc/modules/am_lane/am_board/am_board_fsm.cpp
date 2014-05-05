/*!
 * @file am_board_fsm.cpp
 * @author Christian Amstutz
 * @date Apr 16, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_board_fsm.hpp"

// *****************************************************************************

const am_board_fsm::fsm_states am_board_fsm::IDLE = 0x01;
const am_board_fsm::fsm_states am_board_fsm::RX_HIT = 0x02;
const am_board_fsm::fsm_states am_board_fsm::PROCESS_ROAD = 0x03;
const am_board_fsm::fsm_states am_board_fsm::WRITE_ROAD = 0x04;

// *****************************************************************************

/*!
 * @class am_board_fsm
 *
 */

am_board_fsm::am_board_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        write_en(NR_DETECTOR_LAYERS, "write_en"),
        road_buffer_empty("road_buffer_empty"),
        process_roads("process_roads"),
        write_roads("write_roads")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(fsm);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void am_board_fsm::fsm()
{
    while (1)
    {
        wait();

        switch (state)
        {
        case IDLE:
            process_roads = false;
            write_roads = false;
            if (one_write_en_active())
            {
                state = RX_HIT;
            }
            else
            {
                state = IDLE;
            }
            break;

        case RX_HIT:
            process_roads = false;
            write_roads = false;
            if (one_write_en_active())
            {
                state = RX_HIT;
            }
            else
            {
                state = PROCESS_ROAD;
            }
            break;

        case PROCESS_ROAD:
            process_roads = true;
            write_roads = false;
            state = WRITE_ROAD;
            break;

        case WRITE_ROAD:
            process_roads = false;
            write_roads = true;
            if (road_buffer_empty)
            {
                state = IDLE;
            }
            else
            {
                state = WRITE_ROAD;
            }
            break;

        default:
            state = IDLE;
        }
    }
}

// *****************************************************************************
bool am_board_fsm::one_write_en_active()
{
    bool write_en_active = false;

    for (auto& wren_single : write_en)
    {
        if (wren_single == true)
        {
            write_en_active = true;
            break;
        }
    }

    return (write_en_active);
}
