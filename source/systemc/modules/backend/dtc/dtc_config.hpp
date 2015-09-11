/*!
 * @file dtc_config.hpp
 * @author Christian Amstutz
 * @date September 2, 2015
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
    friend class dtc;

private:
    std::vector<sensor_module_address> sensor_modules;

public:
    unsigned int id;
    dtc_type_config type;
    std::vector<dtc_input_unit_config> input_units;

    dtc_config();

    void add_sensor_module(const sensor_module_address& sensor_module);
    unsigned int get_input_nr() const;
    std::vector<sensor_module_address> get_sensor_modules() const;
};
