/*!
 * @file dtc_config.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_controller_config.hpp"
#include "dtc_input_unit_config.hpp"
#include "dtc_output_unit_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class dtc_config
{
public:
    unsigned int input_nr;
    unsigned int collection_cycles;

    dtc_controller_config controller;
    dtc_input_unit_config input_unit;
    dtc_output_unit_config output_unit;
};
