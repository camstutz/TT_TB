/*!
 * @file hit_generator_config.hpp
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

#include "../../data_formats/stub/stub_config.hpp"
#include "../../modules/frontend/sensor_module_address.hpp"

#include <string>
#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class hit_generator_config
{
public:
    std::string input_file;

    stub_config output_stub_cbc;
    stub_config output_stub_mpa;

    std::vector<sensor_module_address> sensor_module_addresses;
};
