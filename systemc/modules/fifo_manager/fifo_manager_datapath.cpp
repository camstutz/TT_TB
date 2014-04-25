/*!
 * @file fifo_manager_datapath.cpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager_datapath.hpp"

// *****************************************************************************

/*!
 * @class fifo_manager_datapath
 *
 * The module is sensitive to ...
 */

fifo_manager_datapath::fifo_manager_datapath(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        buffer_write_en(NR_AM_BOARDS, "buffer_write_en"),
        buffer_read_en(NR_AM_BOARDS, "buffer_read_en"),
        time_stamp("time_stamp"),
        stub_in(NR_DO_OUT_STUBS, "stub_in"),
        fifo_out(NR_AM_BOARDS, "fifo_out")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_stubs);
        sensitive << clk.pos();
    SC_THREAD(write_fifos);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void fifo_manager_datapath::read_stubs()
{
    while (1)
    {
        wait();

    }

}

// *****************************************************************************
void fifo_manager_datapath::write_fifos()
{
    while(1)
    {
        wait();

    }

}
