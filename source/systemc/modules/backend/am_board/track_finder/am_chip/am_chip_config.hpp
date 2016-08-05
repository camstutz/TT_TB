/*!
 * @file am_chip_config.hpp
 * @author Christian Amstutz
 * @date August 4, 2016
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "am_chip_write_ctrl_config.hpp"

#include "../../../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class am_chip_config
{
friend class am_chip;

private:
    unsigned int layer_nr;
    unsigned int road_detection_threshold;
    unsigned int latency_cycles;

    am_chip_write_ctrl_config write_ctrl;

public:
    am_chip_config();

    void set_layer_nr(unsigned int layer_nr);
    void set_road_detection_threshold(unsigned int threshold);
    void set_latency(unsigned int cycles);
};
