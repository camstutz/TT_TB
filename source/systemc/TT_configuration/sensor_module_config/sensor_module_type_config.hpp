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
#include "gbt_config.hpp"

#include <boost/optional.hpp>

// *****************************************************************************
/*!
 * @brief
 */
class sensor_module_type_config
{
public:
    unsigned int side_count = 2;           // right now fixed as GBT only allows 2 sides
    unsigned int fe_chip_per_side;

    frontend_chip_config frontend_chip_type;
    data_concentrator_config data_concentrator_type;
    gbt_config gbt_type;
};
