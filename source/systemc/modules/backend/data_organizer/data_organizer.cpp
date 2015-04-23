/*!
 * @file data_organizer.cpp
 * @author Christian Amstutz
 * @date April 17, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "data_organizer.hpp"

// *****************************************************************************

const unsigned int data_organizer::dtc_input_nr = NR_DTC_PER_PRB;
const unsigned int data_organizer::proc_unit_nr = NR_PRB_PER_TRIGGER_TOWER;

// *****************************************************************************

/*!
 * @class dtc_input_unit
 *
 * The module is sensitive to ...
 */

data_organizer::data_organizer(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        dtc_inputs(dtc_input_nr, "dtc_inputs"),
        proc_unit_outputs(proc_unit_nr, "proc_unit_output"),
        stub_buffer_input_fifo("stub_buffer_input_fifo"),
        bunch_request_sig("bunch_request_sig"),
        stub_buffer_output_fifo("stub_buffer_output"),
        in_collector("in_collector"),
        stub_buffer("stub_buffer"),
        demultiplexer("demultiplexer", 1, 0)
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    in_collector.frame_inputs.bind(dtc_inputs);
    in_collector.stub_output.bind(stub_buffer_input_fifo);

    stub_buffer.stub_input.bind(stub_buffer_input_fifo);
    stub_buffer.bunch_crossing_select.bind(bunch_request_sig);
    stub_buffer.stub_output.bind(stub_buffer_output_fifo);

    demultiplexer.clk.bind(clk);
    demultiplexer.bunch_crossing_request.bind(bunch_request_sig);
    demultiplexer.stub_input[0].bind(stub_buffer_output_fifo);
    sc_map_linear<sc_out<proc_unit_output_t> >::iterator proc_unit_out_it = proc_unit_outputs.begin();
    sc_map_linear<sc_out<typename do_demux::output_t> >::iterator demux_out_it = demultiplexer.proc_unit_outputs.begin();
    for (; demux_out_it != demultiplexer.proc_unit_outputs.end(); ++demux_out_it)
    {
        demux_out_it->bind(*proc_unit_out_it);

        ++proc_unit_out_it;
    }

    return;
}
