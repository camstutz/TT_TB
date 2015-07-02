/*!
 * @file time_demux_config.hpp
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

// *****************************************************************************
/*!
 * @brief
 */
class time_demux_config
{
public:
    unsigned int layer_nr;
    unsigned int proc_unit_nr;
    int timer_start;
    unsigned int bx_divider;
    unsigned int bx_offset;
};
