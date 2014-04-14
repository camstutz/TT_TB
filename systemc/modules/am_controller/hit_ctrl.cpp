/*!
 * @file hit_ctrl.cpp
 * @author Christian Amstutz
 * @date Apr 14, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_ctrl.hpp"

// *****************************************************************************

/*!
 * @class hit_ctrl
 *
 * The module is sensitive to ...
 */

hit_ctrl::hit_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        new_hit(NR_DETECTOR_LAYERS, "new_hit"),
        wr_hit_lamb(NR_DETECTOR_LAYERS, "wr_hit_lamb"),
        init_event("init_ev"),
        stub_inputs(NR_DETECTOR_LAYERS, "stub_input"),
        hee_reg(NR_DETECTOR_LAYERS, "hee_reg"),
        write_en(NR_DETECTOR_LAYERS, "write_en"),
        stub_output(NR_DETECTOR_LAYERS, "stub_output"),
        hit_controllers(NR_DETECTOR_LAYERS, "hit_controller")
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}
