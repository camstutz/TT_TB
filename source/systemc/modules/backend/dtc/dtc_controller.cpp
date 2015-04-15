/*!
 * @file dtc_controller.cpp
 * @author Christian Amstutz
 * @date April 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_controller.hpp"

// *****************************************************************************

const unsigned int dtc_controller::fe_collect_cycles = NR_DC_WINDOW_CYCLES;

// *****************************************************************************

/*!
 * @class dtc_output_unit
 *
 * The module is sensitive to ...
 */

dtc_controller::dtc_controller(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        bunch_crossing("bunch_crossing"),
        write_buffer("write_buffer"),
        read_buffer("read_buffer")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(update_signals);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void dtc_controller::update_signals()
{
    bx_counter = -1;

    while (1)
    {
        ++bx_counter;

        bunch_crossing.write(bx_counter % fe_collect_cycles);
        write_buffer.write((bx_counter / fe_collect_cycles) % 2);
        read_buffer.write(((bx_counter + fe_collect_cycles)/ fe_collect_cycles) % 2);

        wait();
    }

}
