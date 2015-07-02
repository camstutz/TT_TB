/*!
 * @file track_trigger_config.hpp
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

#include "sensor_module_config/frontend_chip_config.hpp"
#include "sensor_module_config/data_concentrator_config.hpp"
#include "sensor_module_config/sensor_module_config.hpp"
#include "../modules/backend/trigger_tower_config.hpp"

#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class track_trigger_config
{
public:
    frontend_chip_config cbc_frontend_chip;
    frontend_chip_config mpa_frontend_chip;
    data_concentrator_config cbc_data_concentrator;
    data_concentrator_config mpa_data_concentrator;
    sensor_module_type_config cbc_sensor_module;
    sensor_module_type_config mpa_sensor_module;

    trigger_tower_config trigger_tower;

    std::vector<sensor_module_config> sensor_modules;
};
