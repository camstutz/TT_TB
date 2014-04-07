/*!
 * @file am_board_fsm.cpp
 * @author Christian Amstutz
 * @date Apr 7, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_board_fsm.hpp"

// *****************************************************************************

/*!
 * @class fifo_fsm
 *
 * The module is sensitive to clk.pos().
 */

am_board_fsm::am_board_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        write_en(NR_DETECTOR_LAYERS, "write_en")
        // todo: add missing
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
            next_pattern_ready = true;
            process_roads = false;
            write_roads = false;
            if (one_write_en_active())
            {
                state = IDLE;
            }
            else
            {
                state = RX_HIT;
            }
            break;

        case RX_HIT:
            next_pattern_ready = false;
            process_roads = false;
            write_roads = false;
            if (one_write_en_active())
            {
                state = PROCESS_ROAD;
            }
            else
            {
                state = RX_HIT;
            }
            break;

        case PROCESS_ROAD:
            next_pattern_ready = false;
            process_roads = true;
            write_roads = false;
            state = WRITE_ROAD;
            break;

        case WRITE_ROAD:
            next_pattern_ready = false;
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

    for (auto wren_single : write_en)
    {
        if (wren_single == true)
        {
            write_en_active = true;
            break;
        }
    }

    return (write_en_active);
}
