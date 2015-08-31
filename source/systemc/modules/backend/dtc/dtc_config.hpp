/*!
 * @file dtc_config.hpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_controller_config.hpp"
#include "dtc_input_unit_config.hpp"
#include "dtc_output_unit_config.hpp"

#include "../../frontend/sensor_module/sensor_module_address.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class dtc_config
{
public:
    unsigned int collection_cycles;
    unsigned int bx_buffer_FIFO_size;

    dtc_controller_config controller;
    dtc_input_unit_config input_unit;
    dtc_output_unit_config output_unit;

    std::vector<sensor_module_address> sensor_modules;
};
