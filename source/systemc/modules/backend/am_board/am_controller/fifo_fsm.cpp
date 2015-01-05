/*!
 * @file fifo_fsm.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "fifo_fsm.hpp"

// *****************************************************************************

const fifo_fsm::fsm_states fifo_fsm::IDLE = 0x01;
const fifo_fsm::fsm_states fifo_fsm::RX_DATA = 0x02;
const fifo_fsm::fsm_states fifo_fsm::STDBY = 0x04;

// *****************************************************************************

/*!
 * @class fifo_fsm
 *
 * The module is sensitive to clk.pos().
 */

fifo_fsm::fifo_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        fifo_not_empty("fifo_not_empty"),
        pop("pop"),
        pok("pok"),
        fifo_read_en("fifo_read_en"),
        reg_en("reg_en")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(state_logic);
        sensitive << clk.pos();
    SC_THREAD(combinatorial);
        sensitive << current_state << fifo_not_empty << pop << hee_reg_before;
    SC_THREAD(delay_pok)
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    current_state = IDLE;
    next_state = IDLE;

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void fifo_fsm::state_logic()
{
    while (1)
    {
        wait();

        current_state.write(next_state.read());
    }

}

// *****************************************************************************
void fifo_fsm::combinatorial()
{
    while (1)
    {
        wait();

        switch (current_state)
        {
        case IDLE:
            fifo_read_en.write(fifo_not_empty.read());
            reg_en.write(false);
            if (fifo_not_empty.read() == true)
            {
                next_state = RX_DATA;
            }
            else
            {
                next_state = IDLE;
            }
            break;

        case RX_DATA:
            fifo_read_en.write(pop.read() & fifo_not_empty.read() & !hee_reg_before.read());
            reg_en.write(pop.read());
            if (pop.read() == false)
            {
                next_state = STDBY;
            }
            else
            {
                next_state = RX_DATA;
            }
            break;

        case STDBY:
            fifo_read_en.write(false);
            reg_en.write(false);
            if (pop.read() & fifo_not_empty.read())
            {
                next_state = IDLE;
            }
            else
            {
                next_state = STDBY;
            }
            break;

        default:
            next_state = IDLE;
        }
    }
}

// *****************************************************************************
void fifo_fsm::delay_pok()
{
    while (1)
    {
        wait();

        fifo_read_en_d1.write(fifo_read_en.read());
        pok.write(fifo_read_en_d1.read());
    }

}
