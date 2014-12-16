/*!
 * @file am_chip_fsm.cpp
 * @author Christian Amstutz
 * @date November 15, 2014
 *
 * @brief File contains the implementation of the AM board FSM.
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_chip_fsm.hpp"

// *****************************************************************************

const am_chip_fsm::fsm_states am_chip_fsm::IDLE = 0x01;
const am_chip_fsm::fsm_states am_chip_fsm::RX_HIT = 0x02;
const am_chip_fsm::fsm_states am_chip_fsm::PROCESS_ROAD = 0x03;
const am_chip_fsm::fsm_states am_chip_fsm::WRITE_ROAD = 0x04;

// *****************************************************************************

/*!
 * @class am_chip_fsm
 *
 */

am_chip_fsm::am_chip_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        write_en(NR_DETECTOR_LAYERS, "write_en"),
        road_buffer_empty("road_buffer_empty"),
        process_roads("process_roads"),
        write_roads("write_roads")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(combinatorial);
        sensitive << current_state << road_buffer_empty;
        write_en.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;
    next_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void am_chip_fsm::state_logic()
{
    while (1)
    {
        wait();

        current_state.write(next_state.read());
    }

}

// *****************************************************************************
void am_chip_fsm::combinatorial()
{
    while (1)
    {
        wait();

        switch (current_state)
        {
        case IDLE:
            process_roads = false;
            write_roads = false;
            if (one_write_en_active())
            {
                next_state = RX_HIT;
            }
            else
            {
                next_state = IDLE;
            }
            break;

        case RX_HIT:
            process_roads = false;
            write_roads = false;
            if (one_write_en_active())
            {
                next_state = RX_HIT;
            }
            else
            {
                next_state = PROCESS_ROAD;
            }
            break;

        case PROCESS_ROAD:
            process_roads = true;
            write_roads = false;
            next_state = WRITE_ROAD;
            break;

        case WRITE_ROAD:
            process_roads = false;
            write_roads = true;
            if (road_buffer_empty)
            {
                next_state = IDLE;
            }
            else
            {
                next_state = WRITE_ROAD;
            }
            break;

        default:
            next_state = IDLE;
        }
    }
}

// *****************************************************************************
bool am_chip_fsm::one_write_en_active()
{
    bool write_en_active = false;

    sc_map_linear<sc_in<bool> >::iterator wr_en_sig_it = write_en.begin();
    for (; wr_en_sig_it != write_en.end(); ++wr_en_sig_it)
    {
        if (*wr_en_sig_it == true)
        {
            write_en_active = true;
            break;
        }
    }

    return (write_en_active);
}
