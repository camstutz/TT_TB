/*!
 * @file dtc_controller.cpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_controller.hpp"

// *****************************************************************************

/*!
 * @class dtc_output_unit
 *
 * The module is sensitive to ...
 */

dtc_controller::dtc_controller(sc_module_name _name,
        dtc_controller_config configuration) :
        sc_module(_name),
        fe_collect_cycles(configuration.fe_collect_cycles),
        clk("clk"),
        bunch_crossing("bunch_crossing"),
        write_buffer("write_buffer"),
        read_buffer("read_buffer"),
        bx_counter(-1)
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
    while (1)
    {
        ++bx_counter;

        bunch_crossing.write(bx_counter % fe_collect_cycles);
        write_buffer.write((bx_counter / fe_collect_cycles) % 2);
        read_buffer.write(((bx_counter + fe_collect_cycles)/ fe_collect_cycles) % 2);

        wait();
    }

}
