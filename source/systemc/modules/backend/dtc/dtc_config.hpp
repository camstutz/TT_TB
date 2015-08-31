/*!
 * @file dtc_config.hpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_type_config.hpp"

#include "../../frontend/sensor_module/sensor_module_address.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class dtc_config
{
public:
    dtc_type_config type;

    std::vector<sensor_module_address> sensor_modules;
};
