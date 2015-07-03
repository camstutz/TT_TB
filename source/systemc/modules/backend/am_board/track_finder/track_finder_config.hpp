/*!
 * @file track_finder_config.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "road_processor/road_processor_config.hpp"
#include "hit_buffer/hit_buffer_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class track_finder_config
{
public:
    unsigned int layer_nr;

    road_processor_config road_processor;
    hit_buffer_config hit_buffer;
};
