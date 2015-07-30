/*!
 * @file hit_generator_config.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../data_formats/stub_config.hpp"

#include <string>

// *****************************************************************************
/*!
 * @brief
 */
class hit_generator_config
{
public:
    std::string input_file;
    stub_config output_stub;
};
