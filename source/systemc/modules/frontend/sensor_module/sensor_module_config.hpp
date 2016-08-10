/*!
 * @file sensor_module_config.hpp
 * @author Christian Amstutz
 * @date August 28, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sensor_module_address.hpp"
#include "sensor_module_type_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class sensor_module_config
{
public:
    const sensor_module_type_config* type;

    unsigned int id;
    sensor_module_address address;

    sensor_module_config();
    sensor_module_config(const sensor_module_type_config* type, const unsigned int id, const sensor_module_address& address);
};
