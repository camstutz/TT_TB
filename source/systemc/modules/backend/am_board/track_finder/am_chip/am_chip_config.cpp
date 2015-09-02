/*!
 * @file am_chip_config.cpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_chip_config.hpp"

// *****************************************************************************
am_chip_config::am_chip_config()
{
    set_layer_nr(LAYER_DEFAULT);
    set_latency(0);

    return;
}

// *****************************************************************************
void am_chip_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    write_ctrl.layer_nr = layer_nr;

    return;
}

// *****************************************************************************
void am_chip_config::set_road_detection_threshold(unsigned int threshold)
{
    this->road_detection_threshold = threshold;

    return;
}

// *****************************************************************************
void am_chip_config::set_latency(unsigned int cycles)
{
    this->latency_cycles = cycles;

    return;
}
