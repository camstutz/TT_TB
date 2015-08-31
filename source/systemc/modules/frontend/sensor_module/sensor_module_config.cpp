/*!
 * @file sensor_module_config.cpp
 * @author Christian Amstutz
 * @date August 25, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sensor_module_config.hpp"

// *****************************************************************************
sensor_module_config::sensor_module_config() :
        id(0),
        address(sensor_module_address(0,0,0))
{}

// *****************************************************************************
sensor_module_config::sensor_module_config(const sensor_module_type_config type,
        unsigned int id, sensor_module_address address) :
        type(type),
        id(id),
        address(address)
{}

// *****************************************************************************
//sensor_module_config::sensor_module_config(const sensor_module_config& original)
//{
//    type = original.type;
//    id = original.id;
//    address = original.address;
//
//    return;
//}
