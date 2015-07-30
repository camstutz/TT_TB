/*!
 * @file track_trigger_config.hpp
 * @author Christian Amstutz
 * @date July 30, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/hit_generator/hit_generator_config.hpp"
#include "../modules/frontend/frontend_chip_config.hpp"
#include "../modules/frontend/data_concentrator_config.hpp"
#include "../modules/frontend/sensor_module_config.hpp"
#include "../modules/frontend/gbt_config.hpp"
#include "../modules/backend/dtc/dtc_config.hpp"
#include "../modules/backend/trigger_tower_config.hpp"

#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class track_trigger_config
{
public:
    hit_generator_config hit_generator;
    sensor_module_type_config cbc_sensor_module;
    sensor_module_type_config mpa_sensor_module;
    frontend_chip_config cbc_frontend_chip;
    frontend_chip_config mpa_frontend_chip;
    gbt_config gbt;
    dtc_config dtc;
    data_concentrator_config cbc_data_concentrator;
    data_concentrator_config mpa_data_concentrator;

    trigger_tower_config trigger_tower;

    sensor_module_config cbc_sensor_module_test;
    sensor_module_config mpa_sensor_module_test;
    std::vector<sensor_module_config> sensor_modules;
};
