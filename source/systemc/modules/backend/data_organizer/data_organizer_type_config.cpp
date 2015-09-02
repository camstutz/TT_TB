/*!
 * @file data_organizer_type_config.hpp
 * @author Christian Amstutz
 * @date September 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "data_organizer_type_config.hpp"

// *****************************************************************************
data_organizer_type_config::data_organizer_type_config()
{
    set_proc_unit_nr(PRB_NR_PER_TOWER_DEFAULT);

    demultiplexer.layer_nr = 1;   // fix

    set_stub_buffer_in_FIFO_size(DO_STUB_IN_FIFO_DEFAULT);
    set_stub_buffer_out_FIFO_size(DO_STUB_OUT_FIFO_DEFAULT);

    return;
}

// *****************************************************************************
void data_organizer_type_config::set_proc_unit_nr(unsigned int proc_unit_nr)
{
    this->proc_unit_nr = proc_unit_nr;

    demultiplexer.proc_unit_nr = proc_unit_nr;

    return;
}

// *****************************************************************************
void data_organizer_type_config::set_stub_buffer_in_FIFO_size(
        unsigned int stub_buffer_in_FIFO_size)
{
    this->stub_buffer_in_FIFO_size = stub_buffer_in_FIFO_size;

    return;
}

// *****************************************************************************
void data_organizer_type_config::set_stub_buffer_out_FIFO_size(
        unsigned int stub_buffer_out_FIFO_size)
{
    this->stub_buffer_out_FIFO_size = stub_buffer_out_FIFO_size;

    return;
}
