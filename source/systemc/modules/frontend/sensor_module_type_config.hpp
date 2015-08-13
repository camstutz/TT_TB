/*!
 * @file sensor_module_type_config.hpp
 * @author Christian Amstutz
 * @date July 21, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "frontend_chip/frontend_chip_config.hpp"
#include "data_concentrator/data_concentrator_config.hpp"
#include "gbt/gbt_config.hpp"

#include <boost/optional.hpp>

// *****************************************************************************
/*!
 * @brief
 */
class sensor_module_type_config
{
public:
    unsigned int side_count;                   // right now fixed as GBT only allows 2 sides
    unsigned int fe_chip_per_side;

    frontend_chip_config frontend_chip;
    data_concentrator_config data_concentrator;
    gbt_config gbt;
};
