/*!
 * @file road_analyzer_config.hpp
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

#include <string>

// *****************************************************************************
/*!
 * @brief
 */
class road_analyzer_config
{
public:
    std::string output_file;

    unsigned int nr_inputs;
    unsigned int nr_layers;
};
