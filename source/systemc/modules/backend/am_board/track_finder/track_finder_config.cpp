/*!
 * @file track_finder_config.cpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "track_finder_config.hpp"

// *****************************************************************************
track_finder_config::track_finder_config()
{
    set_layer_nr(LAYER_DEFAULT);

    return;
}

// *****************************************************************************
void track_finder_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    hit_processor.set_layer_nr(layer_nr);
    am_chip.set_layer_nr(layer_nr);
    road_processor.layer_nr = layer_nr;
    pattern_memory.layer_nr = layer_nr;
    hit_buffer.set_layer_nr(layer_nr);

    return;
}
