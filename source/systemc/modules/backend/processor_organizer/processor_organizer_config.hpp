/*!
 * @file processor_organizer_config.hpp
 * @author Christian Amstutz
 * @date July 1, 2015
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

    po_layer_splitter_config layer_splitter;
    input_collector_config input_collector;
    time_demux_config demultiplexer;
};
