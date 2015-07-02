/*!
 * @file data_concentrator_config.hpp
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

#include "frontend_chip_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class data_concentrator_config
{
public:
    frontend_chip_config frontend_chip_type;

    unsigned int fe_chips_count;
    unsigned int max_output_stubs;
    unsigned int output_window_cycles;
};
