/*!
 * @file processor_organizer_config.cpp
 * @author Christian Amstutz
 * @date October 2, 2015
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
    //set_do_input_nr(PRB_NR_PER_TOWER_DEFAULT);
    //set_processor_output_nr(PRB_NR_PER_TOWER_DEFAULT);
    set_do_input_nr(0);
    set_processor_output_nr(0);
    set_stub_buffer_in_FIFO_size(PO_STUB_IN_FIFO_DEFAULT);
    set_stub_buffer_out_FIFO_size(PO_STUB_OUT_FIFO_DEFAULT);
    set_layer_splittet_FIFO_size(PO_LAYER_SPLITTET_FIFO_DEFAULT);

    return;
}

// *****************************************************************************
void processor_organizer_config::add_do()
{
    set_do_input_nr(do_input_nr+1);

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
void processor_organizer_config::add_layer(const unsigned int layer_nr)
{
    layers.insert(layer_nr);

    demultiplexer.layer_nr = layers.size();

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
