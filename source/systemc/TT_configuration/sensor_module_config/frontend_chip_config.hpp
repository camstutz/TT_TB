/*!
 * @file frontend_chip_config.hpp
 * @author Christian Amstutz
 * @date June 25, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../TT_configuration/sensor_module_config/fe_chip_output_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class frontend_chip_config
{
public:
    fe_chip_output_config output_format;

    unsigned int max_stubs_per_cycle;
    unsigned int collection_cycles;
};
