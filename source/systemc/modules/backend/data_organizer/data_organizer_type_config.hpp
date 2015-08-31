/*!
 * @file data_organizer_type_config.hpp
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

#include "../common/time_demux_config.hpp"
#include "../common/input_collector_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class data_organizer_type_config
{
public:
    unsigned int proc_unit_nr;

    unsigned int stub_buffer_in_FIFO_size;
    unsigned int stub_buffer_out_FIFO_size;

    input_collector_config input_collector;
    time_demux_config demultiplexer;
};
