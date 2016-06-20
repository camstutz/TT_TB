/*!
 * @file processor_organizer.cpp
 * @author Christian Amstutz
 * @date July 1, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "processor_organizer.hpp"

// *****************************************************************************

/*!
 * @class process_organizer
 *
 * The module is sensitive to ...
 */

processor_organizer::processor_organizer(sc_module_name _name,
        const processor_organizer_config& configuration) :
        sc_module(_name),
        do_input_nr(configuration.do_input_nr),
        layer_nr(configuration.layers.size()),
        processor_output_nr(configuration.processor_output_nr),
        clk("clk"),
        do_inputs(do_input_nr, "do_inputs"),
        processor_outputs(processor_output_nr, layer_nr, "processor_output"),
        stub_buffer_input_fifo("stub_buffer_input_fifo", 500),
        bunch_request_sig("bunch_request_sig"),
        stub_buffer_output_fifo("stub_buffer_output", 500),
        splitted_stubs_fifos(layer_nr, "splitted_stubs_fifo", 500),
        in_collector("in_collector", configuration.input_collector),
        stub_buffer("stub_buffer"),
        layer_splitter("layer_splitter", configuration.layer_splitter),
        demultiplexer("demultiplexer", configuration.demultiplexer)
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    in_collector.frame_inputs.bind(do_inputs);
    in_collector.stub_output.bind(stub_buffer_input_fifo);

    stub_buffer.stub_input.bind(stub_buffer_input_fifo);
    stub_buffer.bunch_crossing_select.bind(bunch_request_sig);
    stub_buffer.stub_output.bind(stub_buffer_output_fifo);

    layer_splitter.input_stubs.bind(stub_buffer_output_fifo);
    layer_splitter.splitted_stubs.bind(splitted_stubs_fifos);

    demultiplexer.clk.bind(clk);
    demultiplexer.bunch_crossing_request.bind(bunch_request_sig);
    demultiplexer.stub_input.bind(splitted_stubs_fifos);
    demultiplexer.proc_unit_outputs.bind(processor_outputs);

    return;
}
