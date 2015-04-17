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

const unsigned int data_organizer::dtc_input_nr = 2;
const unsigned int data_organizer::proc_unit_nr = 4;

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
        demultiplexer("demultiplexer")
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
    for (unsigned int proc_unit_id = 0; proc_unit_id < proc_unit_nr; ++proc_unit_id)
    {
        demultiplexer.proc_unit_outputs.at(0, proc_unit_id).bind(proc_unit_outputs[proc_unit_id]);
    }

    return;
}
