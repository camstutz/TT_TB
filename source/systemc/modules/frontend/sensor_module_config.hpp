/*!
 * @file sensor_module_config.hpp
 * @author Christian Amstutz
 * @date August 19, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sensor_module_type_config.hpp"

#include <boost/optional.hpp>

// *****************************************************************************
/*!
 * @brief
 */
class sensor_module_config
{
public:
    sensor_module_type_config *type;

    boost::optional<unsigned int> id;
    boost::optional<unsigned int> layer;
    boost::optional<unsigned int> ladder;
    boost::optional<unsigned int> module;
};
