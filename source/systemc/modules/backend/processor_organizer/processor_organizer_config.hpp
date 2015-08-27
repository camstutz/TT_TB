/*!
 * @file processor_organizer_config.hpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../common/input_collector_config.hpp"
#include "../common/time_demux_config.hpp"
#include "po_layer_splitter_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class processor_organizer_config
{
public:
    unsigned int do_input_nr;
    unsigned int layer_nr;
    unsigned int processor_output_nr;

    unsigned int stub_buffer_in_FIFO_size;
    unsigned int stub_buffer_out_FIFO_size;
    unsigned int layer_splittet_FIFO_size;

    po_layer_splitter_config layer_splitter;
    input_collector_config input_collector;
    time_demux_config demultiplexer;
};
