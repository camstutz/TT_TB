/*!
 * @file am_board.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_board.hpp"

// *****************************************************************************

/*!
 * @class am_lane
 */

am_board::am_board(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        fifo_write_en(NR_DETECTOR_LAYERS, "fifo_write_ens"),
        fifo_inputs(NR_DETECTOR_LAYERS, "fifo_inputs"),
        road_write_en("road_write_en"),
        road_output("road_output"),
        fifo_not_empty_sig(NR_DETECTOR_LAYERS, "fifo_not_empty_sig"),
        fifo_read_en_sig(NR_DETECTOR_LAYERS, "fifo_read_en_sig"),
        fifo_stub_out_sig(NR_DETECTOR_LAYERS, "fifo_stub_out_sig"),
        init_ev_sig("init_ev_sig"),
        am_write_en_sig(NR_DETECTOR_LAYERS, "AM_write_en_sig"),
        am_pattern_sig(NR_DETECTOR_LAYERS, "AM_pattern_sig"),
        am_data_ready_sig("am_data_ready_sig"),
        am_road_sig("am_road_sig"),
        stub_fifo_array(NR_DETECTOR_LAYERS, "stub_fifo"),
        AMcontroller("AM_controller"),
        AMboard("AM_board")
{
    // ----- Module instance / channel binding ---------------------------------
    unsigned int layer = 0;
    sc_map_linear<stub_fifo<STUB_FIFO_DEPTH> >::iterator fifo_it = stub_fifo_array.begin();
    for (; fifo_it != stub_fifo_array.end(); ++fifo_it)
    {
        fifo_it->clk.bind(clk);
        fifo_it->write_en.bind(fifo_write_en[layer]);
        fifo_it->stub_in.bind(fifo_inputs[layer]);
        fifo_it->not_empty.bind(fifo_not_empty_sig[layer]);
        fifo_it->read_en.bind(fifo_read_en_sig[layer]);
        fifo_it->stub_out.bind(fifo_stub_out_sig[layer]);

        ++layer;
    }

    AMcontroller.clk.bind(clk);
    AMcontroller.fifo_not_empty.bind(fifo_not_empty_sig);
    AMcontroller.fifo_read_en.bind(fifo_read_en_sig);
    AMcontroller.stub_inputs.bind(fifo_stub_out_sig);
    AMcontroller.init_ev.bind(init_ev_sig);
    AMcontroller.am_write_en.bind(am_write_en_sig);
    AMcontroller.am_stub_outputs.bind(am_pattern_sig);
    AMcontroller.data_ready.bind(am_data_ready_sig);
    AMcontroller.road_in.bind(am_road_sig);
    AMcontroller.road_write_en.bind(road_write_en);
    AMcontroller.road_output.bind(road_output);

    AMboard.clk.bind(clk);
    AMboard.init_ev.bind(init_ev_sig);
    AMboard.write_en.bind(am_write_en_sig);
    AMboard.pattern_inputs.bind(am_pattern_sig);
    AMboard.data_ready.bind(am_data_ready_sig);
    AMboard.road_output.bind(am_road_sig);

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    return;
}
