/*!
 * @file hit_ctrl.cpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
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
        hee_reg_before(NR_DETECTOR_LAYERS, "hee_reg_before"),
        hee_reg(NR_DETECTOR_LAYERS, "hee_reg"),
        write_en(NR_DETECTOR_LAYERS, "write_en"),
        stub_output(NR_DETECTOR_LAYERS, "stub_output"),
        event_tag("event_tag"),
        tag_signals(NR_DETECTOR_LAYERS-1, "tag_signals"),
        hit_controllers(NR_DETECTOR_LAYERS, "hit_controller")

{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    unsigned int id = 0;
    sc_map_linear<hit_ctrl_single_line>::iterator hit_controller_it = hit_controllers.begin();
    for (; hit_controller_it != hit_controllers.end(); ++hit_controller_it)
    {
        hit_controller_it->clk.bind(clk);
        hit_controller_it->new_hit.bind(new_hit[id]);
        hit_controller_it->wr_hit_lamb.bind(wr_hit_lamb[id]);
        hit_controller_it->init_event.bind(init_event);
        hit_controller_it->stub_input.bind(stub_inputs[id]);
        hit_controller_it->hee_reg_before.bind(hee_reg_before[id]);
        hit_controller_it->hee_reg.bind(hee_reg[id]);
        hit_controller_it->write_en.bind(write_en[id]);
        hit_controller_it->stub_output.bind(stub_output[id]);

        if (id == 0)
        {
        	hit_controller_it->stub_tag.bind(event_tag);
        }
        else
        {
            hit_controller_it->stub_tag.bind(tag_signals[id-1]);
        }

        ++id;
    }

    return;
}
