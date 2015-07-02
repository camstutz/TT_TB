/*!
 * @file data_organizer_config.hpp
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

#include "../common/time_demux_config.hpp"
#include "../common/input_collector_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class data_organizer_config
{
public:
    unsigned int dtc_input_nr;
    unsigned int proc_unit_nr;
    int counter_correction;

    input_collector_config input_collector;
    time_demux_config demultiplexer;
};
