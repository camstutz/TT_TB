/*!
 * @file sensor_module_type_config.hpp
 * @author Christian Amstutz
 * @date May 15, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "frontend_chip_config.hpp"
#include "data_concentrator_config.hpp"

#include <boost/optional.hpp>

// *****************************************************************************
/*!
 * @brief
 */
class sensor_module_type_config
{
public:
    frontend_chip_config frontend_chip_type;
    data_concentrator_config data_concentrator_type;

    boost::optional<unsigned int> side_count;
    boost::optional<unsigned int> fe_chip_per_side;
};
