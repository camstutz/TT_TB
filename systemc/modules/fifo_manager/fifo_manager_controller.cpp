/*!
 * @file fifo_manager_controller.cpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager_controller.hpp"

// *****************************************************************************

//const fifo_fsm::fsm_states fifo_fsm::IDLE = 0x01;
//const fifo_fsm::fsm_states fifo_fsm::RX_DATA = 0x02;
//const fifo_fsm::fsm_states fifo_fsm::STDBY = 0x04;

// *****************************************************************************

/*!
 * @class fifo_controller
 *
 * The module is sensitive to ...
 */

fifo_manager_controller::fifo_manager_controller(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        buffer_write_en(NR_AM_BOARDS, "buffer_write_en"),
        buffer_read_en(NR_AM_BOARDS, "buffer_read_en"),
        time_stamp("time_stamp"),
        current_state("current_state"),
        next_state("next_state")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(fsm_logic);
        sensitive << current_state;
    SC_THREAD(update_timestamp)
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    //current_state = IDLE;
    //next_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void fifo_manager_controller::state_logic()
{
    while (1)
    {
        wait();

        current_state.write(next_state.read());
    }

}

// *****************************************************************************
void fifo_manager_controller::fsm_logic()
{
    while (1)
    {
        wait();

        switch (current_state)
        {
//        case IDLE:
//
//            break;
//
//        default:
//            next_state = IDLE;
        }
    }
}

// *****************************************************************************
void fifo_manager_controller::update_timestamp()
{
    while (1)
    {
        wait();
    }

}
