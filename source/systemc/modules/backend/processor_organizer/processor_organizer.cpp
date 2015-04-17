/*!
 * @file processor_organizer.cpp
 * @author Christian Amstutz
 * @date April 17, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "processor_organizer.hpp"

// *****************************************************************************

const unsigned int processor_organizer::do_input_nr = 4;
const unsigned int processor_organizer::layer_nr = 6;
const unsigned int processor_organizer::processor_output_nr = 2;

// *****************************************************************************

/*!
 * @class dtc_input_unit
 *
 * The module is sensitive to ...
 */

processor_organizer::processor_organizer(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        do_inputs(do_input_nr, "do_inputs"),
        processor_outputs(processor_output_nr, layer_nr, "processor_output"),
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
    in_collector.frame_inputs.bind(do_inputs);
    in_collector.stub_output.bind(stub_buffer_input_fifo);

    stub_buffer.stub_input.bind(stub_buffer_input_fifo);
    stub_buffer.bunch_crossing_select.bind(bunch_request_sig);
    stub_buffer.stub_output.bind(stub_buffer_output_fifo);

    demultiplexer.clk.bind(clk);
    demultiplexer.bunch_crossing_request.bind(bunch_request_sig);
    demultiplexer.stub_input.bind(stub_buffer_output_fifo);
    demultiplexer.proc_unit_outputs.bind(processor_outputs);

    return;
}
