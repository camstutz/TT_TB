/*!
 * @file am_input_module_config.hpp
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

#include "am_input_module_ctrl_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class am_input_module_config
{
public:
    unsigned int layer_nr;

    am_input_module_ctrl_config controller;
};
