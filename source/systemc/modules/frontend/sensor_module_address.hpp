/*!
 * @file sensor_module_address.hpp
 * @author Christian Amstutz
 * @date August 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <ostream>

// *****************************************************************************
/*!
 * @brief
 */
class sensor_module_address
{
public:
    unsigned int layer;
    unsigned int ladder;
    unsigned int module;

    sensor_module_address();
    sensor_module_address(unsigned int layer, unsigned int ladder, unsigned int module);

    bool operator== (const sensor_module_address& rhs) const;
    bool operator< (const sensor_module_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, sensor_module_address const &v);
};
