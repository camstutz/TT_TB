/*!
 * @file fifo_fsm.cpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_fsm.hpp"

// *****************************************************************************

const fifo_fsm::fsm_states fifo_fsm::IDLE = 0x01;
const fifo_fsm::fsm_states fifo_fsm::RX_DATA = 0x02;
const fifo_fsm::fsm_states fifo_fsm::STDBY = 0x03;

// *****************************************************************************

/*!
 * @class fifo_fsm
 *
 * The module is sensitive to clk.pos().
 */

fifo_fsm::fifo_fsm(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        fifo_not_empty("fifo_not_empty"),
        pop("pop"),
        pok("pok"),
        fifo_read_en("fifo_read_en"),
        reg_en("reg_en")
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
void fifo_fsm::fsm()
{
    while (1)
    {
        wait();

        switch (state)
        {
        case IDLE:
            fifo_read_en.write(fifo_not_empty.read());
            reg_en.write(false);
            if (fifo_not_empty.read() == true)
            {
                state = RX_DATA;
            }
            break;

        case RX_DATA:
            fifo_read_en.write(pop.read() & fifo_not_empty.read());
            reg_en.write(pop.read());
            if (pop.read() == false)
            {
                state = STDBY;
            }
            break;

        case STDBY:
            fifo_read_en.write(false);
            reg_en.write(false);
            if (pop.read() & fifo_not_empty.read())
            {
                state = RX_DATA;
            }
            break;

        default:
            state = IDLE;
        }
    }
}
