/*!
 * @file hit_ctrl_single_line.cpp
 * @author Christian Amstutz
 * @date Apr 14, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_ctrl_single_line.hpp"

// *****************************************************************************

/*!
 * @class hit_ctrl_single_line
 *
 * The module is sensitive to ...
 */

hit_ctrl_single_line::hit_ctrl_single_line(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        new_hit("new_hit"),
        wr_hit_lamb("wr_hit_lamb"),
        init_event("init_ev"),
        stub_input("stub_input"),
        hee_reg("hee_reg"),
        write_en("write_en"),
        stub_output("stub_output")
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}
