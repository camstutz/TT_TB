/*!
 * @file hit_generator_config.hpp
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

#include "../../data_formats/stub/stub_config.hpp"
#include "../../modules/frontend/chip_address.hpp"

#include <string>
#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class hit_generator_config
{
public:
    unsigned int LHC_clock_period_ns;
    std::string input_file;

    stub_config output_stub_cbc;
    stub_config output_stub_mpa;

    std::vector<chip_address> chip_addresses;
};
