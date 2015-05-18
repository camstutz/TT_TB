/*!
 * @file baseline_config.hpp
 * @author Christian Amstutz
 * @date May 15, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sensor_module_config/track_trigger_config.hpp"

track_trigger_config baseline_config()
{
    track_trigger_config baseline_config;

    baseline_config.cbc_front_end_chip.max_stubs_per_cycle = 3;
    baseline_config.cbc_front_end_chip.collection_cycles = 1;

    baseline_config.cbc_front_end_chip.output_format.bx_bits = 0;
    baseline_config.cbc_front_end_chip.output_format.strip_bits = 8;
    baseline_config.cbc_front_end_chip.output_format.pixel_bits = 0;
    baseline_config.cbc_front_end_chip.output_format.bend_bits = 5;

    baseline_config.mpa_front_end_chip.max_stubs_per_cycle = 2;
    baseline_config.mpa_front_end_chip.collection_cycles = 2;

    baseline_config.mpa_front_end_chip.output_format.bx_bits = 1;
    baseline_config.mpa_front_end_chip.output_format.strip_bits = 8;
    baseline_config.mpa_front_end_chip.output_format.pixel_bits = 4;
    baseline_config.mpa_front_end_chip.output_format.bend_bits = 5;

    return baseline_config;
}

