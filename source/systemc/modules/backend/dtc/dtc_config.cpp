/*!
 * @file dtc_config.hpp
 * @author Christian Amstutz
 * @date September 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_config.hpp"

// *****************************************************************************
dtc_config::dtc_config()
{
    type.output_unit.dtc_input_nr = 0;

    return;
}

// *****************************************************************************
void dtc_config::add_sensor_module(const sensor_module_address& sensor_module)
{
    sensor_modules.push_back(sensor_module);
    type.output_unit.dtc_input_nr = get_input_nr();

    return;
}

// *****************************************************************************
unsigned int dtc_config::get_input_nr() const
{
    return sensor_modules.size();
}

// *****************************************************************************
std::vector<sensor_module_address> dtc_config::get_sensor_modules() const
{
    return sensor_modules;
}
