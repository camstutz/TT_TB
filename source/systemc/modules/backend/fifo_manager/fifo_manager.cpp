/*!
 * @file fifo_manager.cpp
 * @author Christian Amstutz
 * @date May 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager.hpp"

// *****************************************************************************

/*!
 * @class data_organizer
 *
 * The module is sensitive to clk.pos and the change of the input_buffer.
 */

fifo_manager::fifo_manager(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        stub_in(NR_DETECTOR_LAYERS, NR_DO_OUT_STUBS, "stub_in"),
        fifo_out(NR_AM_BOARDS, NR_DETECTOR_LAYERS, "fifo_out"),
        buf_write_en_sig(NR_AM_BOARDS, "buf_write_en_sig"),
        buf_read_en_sig(NR_AM_BOARDS, "buf_read_en_sig"),
        time_stamp_sig("time_stamp_sig"),
        controller("controller"),
        datapaths(NR_DETECTOR_LAYERS, "datapath")
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    controller.clk.bind(clk);
    controller.rst.bind(rst);
    controller.buffer_write_en.bind(buf_write_en_sig);
    controller.buffer_read_en.bind(buf_read_en_sig);
    controller.time_stamp.bind(time_stamp_sig);

    unsigned int layer = 0;
    sc_map_linear<fifo_manager_datapath>::iterator datapath_it = datapaths.begin();
    for (; datapath_it != datapaths.end(); ++datapath_it)
    {
        datapath_it->clk.bind(clk);
        datapath_it->rst.bind(rst);
        datapath_it->buffer_write_en.bind(buf_write_en_sig);    // todo: Problem in ModelSim
        datapath_it->buffer_read_en.bind(buf_read_en_sig);      // todo: Crash in ModelSim
        datapath_it->time_stamp.bind(time_stamp_sig);

        sc_map_square<sc_in<do_out_data> >::square_iterator inport_iter = stub_in.begin_partial(layer, false, 0, true);
        datapath_it->stub_in.bind_by_iter(inport_iter);
        sc_map_square<sc_out<fm_out_data> >::square_iterator outport_iter = fifo_out.begin_partial(0, true, layer, false);
        datapath_it->fifo_out.bind_by_iter(outport_iter);

        ++layer;
}

    return;
}
