/*!
 * @file hit_generator_config.hpp
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

#include "../../data_formats/stub/stub_config.hpp"
#include "../../modules/frontend/sensor_module/sensor_module_config.hpp"
#include "../../modules/frontend/sensor_module/chip_address.hpp"

#include "../../TT_configuration/configuration_defaults.hpp"

#include <string>
#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class hit_generator_config
{
    friend class hit_generator;

private:
    unsigned int LHC_clock_period_ns;

    std::vector<chip_address> chip_addresses;

public:
    std::string input_file;

    stub_config output_stub_cbc;
    stub_config output_stub_mpa;

    hit_generator_config();
    hit_generator_config(unsigned int LHC_clock_period_ns);

    void set_LHC_clock_period_ns(unsigned int LHC_clock_period_ns);

    void add_chips(const sensor_module_config module);
};
