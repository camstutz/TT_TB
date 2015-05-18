/*!
 * @file track_trigger_config.hpp
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

#include "frontend_chip_config.hpp"
#include "sensor_module_config.hpp"

#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class track_trigger_config
{
public:
    frontend_chip_config cbc_front_end_chip;
    frontend_chip_config mpa_front_end_chip;
    sensor_module_type_config cbc_sensor_module;
    sensor_module_type_config mpa_sensor_module;
    std::vector<sensor_module_config> sensor_modules;
};
