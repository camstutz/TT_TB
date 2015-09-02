/*!
 * @file processor_organizer_config.cpp
 * @author Christian Amstutz
 * @date September 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "processor_organizer_config.hpp"

// *****************************************************************************
processor_organizer_config::processor_organizer_config()
{
    set_do_input_nr(PRB_NR_PER_TOWER_DEFAULT);
    set_layer_nr(LAYER_DEFAULT);
    set_processor_output_nr(PRB_NR_PER_TOWER_DEFAULT);
    set_stub_buffer_in_FIFO_size(PO_STUB_IN_FIFO_DEFAULT);
    set_stub_buffer_out_FIFO_size(PO_STUB_OUT_FIFO_DEFAULT);
    set_layer_splittet_FIFO_size(PO_LAYER_SPLITTET_FIFO_DEFAULT);

    return;
}

// *****************************************************************************
void processor_organizer_config::set_do_input_nr(unsigned int input_nr)
{
    this->do_input_nr = input_nr;

    input_collector.input_nr = input_nr;

    return;
}

// *****************************************************************************
void processor_organizer_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    demultiplexer.layer_nr = layer_nr;
    layer_splitter.layer_nr = layer_nr;

    return;
}

// *****************************************************************************
void processor_organizer_config::set_processor_output_nr(unsigned int output_nr)
{
    this->processor_output_nr = output_nr;

    demultiplexer.proc_unit_nr = output_nr;

    return;
}

// *****************************************************************************
void processor_organizer_config::set_stub_buffer_in_FIFO_size(
        unsigned int stub_buffer_in_FIFO_size)
{
    this->stub_buffer_in_FIFO_size = stub_buffer_in_FIFO_size;

    return;
}

// *****************************************************************************
void processor_organizer_config::set_stub_buffer_out_FIFO_size(
        unsigned int stub_buffer_out_FIFO_size)
{
    this->stub_buffer_out_FIFO_size = stub_buffer_out_FIFO_size;

    return;
}

// *****************************************************************************
void processor_organizer_config::set_layer_splittet_FIFO_size(
        unsigned int layer_splittet_FIFO_size)
{
    this->layer_splittet_FIFO_size = layer_splittet_FIFO_size;

    return;
}
