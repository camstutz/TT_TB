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

#include "../../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class am_input_module_config
{
    friend class am_input_module;

private:
    unsigned int layer_nr;

    am_input_module_ctrl_config controller;

public:
    am_input_module_config();

    void set_layer_nr(unsigned int layer_nr);
};
