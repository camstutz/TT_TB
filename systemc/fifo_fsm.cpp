/*!
 * @file fifo_fsm.cpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_fsm.hpp"

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
        fifo_empty("fifo_empty"),
        pop("pop"),
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
            fifo_read_en.write(fifo_empty.read());
            reg_en.write(false);
            if (fifo_empty.read())
            {
                state = RX_DATA;
            }
            break;

        case RX_DATA:
            fifo_read_en.write(pop.read() & fifo_empty.read());
            reg_en.write(pop.read());
            if (!pop.read())
            {
                state = STDBY;
            }
            break;

        case STDBY:
            fifo_read_en.write(false);
            reg_en.write(false);
            if (pop.read() & fifo_empty.read())
            {
                state = RX_DATA;
            }
            break;
        }
    }
}
