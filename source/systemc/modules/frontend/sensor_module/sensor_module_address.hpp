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

#include "sensor_module_type_config.hpp"
#include "chip_address.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <ostream>

#include <iostream>   // only debug

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
    sensor_module_address(unsigned int module_id);

    std::vector<chip_address> get_chips(const unsigned int nr_segments, const unsigned int nr_chips) const;
    std::vector<chip_address> get_chips(const sensor_module_type_config& sensor_mod_config) const;

    bool operator== (const sensor_module_address& rhs) const;
    bool operator< (const sensor_module_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, sensor_module_address const &v);
};
