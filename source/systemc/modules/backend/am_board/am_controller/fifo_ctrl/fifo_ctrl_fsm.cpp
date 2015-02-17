/*!
 * @file fifo_ctrl_fsm.cpp
 * @author Christian Amstutz
 * @date February 16, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "fifo_ctrl_fsm.hpp"

// *****************************************************************************

const fifo_ctrl_fsm::fsm_states fifo_ctrl_fsm::IDLE = 0x01;
const fifo_ctrl_fsm::fsm_states fifo_ctrl_fsm::START = 0x02;
const fifo_ctrl_fsm::fsm_states fifo_ctrl_fsm::PROCESS = 0x03;
const fifo_ctrl_fsm::fsm_states fifo_ctrl_fsm::WAIT_EVENT_END = 0x04;

// *****************************************************************************

/*!
 * @class fifo_ctrl_fsm
 *
 * The module is sensitive ...
 */

fifo_ctrl_fsm::fifo_ctrl_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        fifo_write_en("fifo_write_en"),
        fifo_not_empty("fifo_not_empty"),
        is_timestamp("is_timestamp"),
        event_active("event_active"),
        event_start("event_start"),
        fifo_read_en("fifo_read_en")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(combinatorial);
        sensitive << current_state << fifo_not_empty << fifo_write_en
                  << event_active << is_timestamp;

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;
    next_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void fifo_ctrl_fsm::state_logic()
{
    while (1)
    {
        wait();

        current_state.write(next_state.read());
    }

}

// *****************************************************************************
void fifo_ctrl_fsm::combinatorial()
{
    while (1)
    {
        wait();

        switch (current_state)
        {
        case IDLE:
            fifo_read_en.write(false);
            event_start.write(false);

            if ((fifo_not_empty.read() == true) &
                (fifo_write_en.read() == false))
            {
                next_state = START;
            }
            else
            {
                next_state = IDLE;
            }
            break;

        case START:
            fifo_read_en.write(false);
            event_start.write(true);

            next_state = PROCESS;
            break;

        case PROCESS:
            fifo_read_en.write(true);
            event_start.write(false);

            if (is_timestamp.read() == true)
            {
                next_state = WAIT_EVENT_END;
            }
            else
            {
                next_state = PROCESS;
            }
            break;

        case WAIT_EVENT_END:
            fifo_read_en.write(false);
            event_start.write(false);

            if (event_active.read() == false)
            {
                next_state = IDLE;
            }
            else
            {
                next_state = WAIT_EVENT_END;
            }
            break;

        default:
            next_state = IDLE;
        }
    }
}
