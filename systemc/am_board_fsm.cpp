/*!
 * @file am_board_fsm.cpp
 * @author Christian Amstutz
 * @date Apr 3, 2014
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
        write_en("write_en"),
        scan_arrray("scan_array"),
        road_ld("road_ld"),
        road_tx("road_tx"),
        output_reg_init("output_reg_init")
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
