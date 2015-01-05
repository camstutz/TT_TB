/*!
 * @file fifo_manager_controller.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "fifo_manager_controller.hpp"

// *****************************************************************************

const fifo_manager_controller::fsm_states fifo_manager_controller::S0_0 = 0x01;
const fifo_manager_controller::fsm_states fifo_manager_controller::S0_1 = 0x02;
const fifo_manager_controller::fsm_states fifo_manager_controller::S0_2 = 0x03;
const fifo_manager_controller::fsm_states fifo_manager_controller::S0_3 = 0x04;
const fifo_manager_controller::fsm_states fifo_manager_controller::S1_0 = 0x05;
const fifo_manager_controller::fsm_states fifo_manager_controller::S1_1 = 0x06;
const fifo_manager_controller::fsm_states fifo_manager_controller::S1_2 = 0x07;
const fifo_manager_controller::fsm_states fifo_manager_controller::S1_3 = 0x08;
const fifo_manager_controller::fsm_states fifo_manager_controller::S2_0 = 0x09;
const fifo_manager_controller::fsm_states fifo_manager_controller::S2_1 = 0x0A;
const fifo_manager_controller::fsm_states fifo_manager_controller::S2_2 = 0x0B;
const fifo_manager_controller::fsm_states fifo_manager_controller::S2_3 = 0x0C;
const fifo_manager_controller::fsm_states fifo_manager_controller::S3_0 = 0x0D;
const fifo_manager_controller::fsm_states fifo_manager_controller::S3_1 = 0x0E;
const fifo_manager_controller::fsm_states fifo_manager_controller::S3_2 = 0x0F;
const fifo_manager_controller::fsm_states fifo_manager_controller::S3_3 = 0x10;

// *****************************************************************************

/*!
 * @class fifo_controller
 *
 * The module is sensitive to ...
 */

fifo_manager_controller::fifo_manager_controller(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
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
        sensitive << current_state << clk.pos();
    SC_THREAD(update_timestamp)
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    current_state = S0_0;
    next_state = S0_0;

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
        case S0_0:
            time_stamp_cnt_en.write(true);
            buffer_write_en[0].write(true);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S0_1;
            break;

        case S0_1:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(false);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S0_2;
            break;

        case S0_2:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(false);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S0_3;
            break;

        case S0_3:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(false);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S1_0;
            break;

        case S1_0:
            time_stamp_cnt_en.write(true);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(true);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S1_1;
            break;

        case S1_1:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(false);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S1_2;
            break;

        case S1_2:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(false);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S1_3;
            break;

        case S1_3:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(false);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S2_0;
            break;

        case S2_0:
            time_stamp_cnt_en.write(true);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(true);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S2_1;
            break;

        case S2_1:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(false);
            buffer_read_en[3].write(true);
            next_state = S2_2;
            break;

        case S2_2:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(false);
            buffer_read_en[3].write(true);
            next_state = S2_3;
            break;

        case S2_3:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(false);
            buffer_read_en[3].write(true);
            next_state = S3_0;
            break;

        case S3_0:
            time_stamp_cnt_en.write(true);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(true);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(true);
            next_state = S3_1;
            break;

        case S3_1:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(false);
            next_state = S3_2;
            break;

        case S3_2:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(false);
            next_state = S3_3;
            break;

        case S3_3:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(true);
            buffer_read_en[1].write(true);
            buffer_read_en[2].write(true);
            buffer_read_en[3].write(false);
            next_state = S0_0;
            break;

        default:
            time_stamp_cnt_en.write(false);
            buffer_write_en[0].write(false);
            buffer_write_en[1].write(false);
            buffer_write_en[2].write(false);
            buffer_write_en[3].write(false);
            buffer_read_en[0].write(false);
            buffer_read_en[1].write(false);
            buffer_read_en[2].write(false);
            buffer_read_en[3].write(false);
            next_state = S0_0;
        }
    }

}

// *****************************************************************************
void fifo_manager_controller::update_timestamp()
{
    time_stamp_cnt = 0;

    while (1)
    {
        wait();

        if (time_stamp_cnt_en.read())
        {
            ++time_stamp_cnt;
            time_stamp.write(time_stamp_cnt);
        }
    }

}
