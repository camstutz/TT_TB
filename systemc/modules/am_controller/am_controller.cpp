/*!
 * @file am_controller.cpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "am_controller.hpp"

// *****************************************************************************

/*!
 * @class am_controller
 */

am_controller::am_controller(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        init("init"),
        fifo_not_empty(NR_DETECTOR_LAYERS, "fifo_empty"),
        stub_inputs(NR_DETECTOR_LAYERS, "stub_input"),
        data_ready("data_ready"),
        road_in("road_in"),
        init_ev("init_ev"),
        fifo_read_en(NR_DETECTOR_LAYERS, "fifo_read_en"),
        am_write_en(NR_DETECTOR_LAYERS, "am_write_en"),
        am_stub_outputs(NR_DETECTOR_LAYERS, "am_stub_en"),
        road_write_en("road_write_en"),
        road_output("road_output"),
        pop_sig(NR_DETECTOR_LAYERS, "pop_sig"),
        pok_sig(NR_DETECTOR_LAYERS, "pok_sig"),
        hit_ctrl_reg_en(NR_DETECTOR_LAYERS, "hit_ctrl_reg_en"),
        hee_reg_sig(NR_DETECTOR_LAYERS, "hee_reg_sig"),
        hit_ctrl_en(NR_DETECTOR_LAYERS, "hit_ctrl_en"),
        road_ctrl_finish_road("road_ctrl_finish_road"),
        select_iam_sig("select_iam_sig"),
        main_am_fsm("main_fsm"),
        fifo_fsm_array(NR_DETECTOR_LAYERS, "FIFO_FSM"),
        hit_controller("hit_ctrl"),
        road_controller("road_ctrl")
{
    // ----- Module instance / channel binding ---------------------------------
    main_am_fsm.clk.bind(clk);
    main_am_fsm.init.bind(init);
    main_am_fsm.pop.bind(pop_sig);
    main_am_fsm.pok.bind(pok_sig);
    main_am_fsm.hee_reg.bind(hee_reg_sig);
    main_am_fsm.en.bind(hit_ctrl_en);
    main_am_fsm.finish_road.bind(road_ctrl_finish_road);
    main_am_fsm.select_iam.bind(select_iam_sig);
    main_am_fsm.init_ev.bind(init_ev);

    unsigned int id = 0;
    for (auto& fifo_fsm: fifo_fsm_array)
    {
        fifo_fsm.clk.bind(clk);
        fifo_fsm.rst.bind(init);
        fifo_fsm.fifo_not_empty.bind(fifo_not_empty[id]);
        fifo_fsm.fifo_read_en.bind(fifo_read_en[id]);
        fifo_fsm.pop.bind(pop_sig[id]);
        fifo_fsm.pok.bind(pok_sig[id]);
        fifo_fsm.reg_en.bind(hit_ctrl_reg_en[id]);

        ++id;
    }

    hit_controller.clk.bind(clk);
    hit_controller.new_hit.bind(hit_ctrl_reg_en);
    hit_controller.wr_hit_lamb.bind(hit_ctrl_en);
    hit_controller.init_event.bind(init_ev_dead);
    hit_controller.hee_reg.bind(hee_reg_sig);
    hit_controller.stub_inputs.bind(stub_inputs);
    hit_controller.write_en.bind(am_write_en);
    hit_controller.stub_output.bind(am_stub_outputs);

    road_controller.clk.bind(clk);
    road_controller.init.bind(init);
    road_controller.sel_word.bind(select_iam_sig);
    road_controller.data_ready_road.bind(data_ready);
    road_controller.road_in.bind(road_in);
    road_controller.finish_road.bind(road_ctrl_finish_road);
    road_controller.write_en_road.bind(road_write_en);
    road_controller.road_out.bind(road_output);

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    return;
}
