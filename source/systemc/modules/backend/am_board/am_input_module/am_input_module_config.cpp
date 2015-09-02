/*!
 * @file am_input_module_config.cpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_input_module_config.hpp"

// *****************************************************************************
am_input_module_config::am_input_module_config()
{
    set_layer_nr(LAYER_DEFAULT);

    return;
}

// *****************************************************************************
void am_input_module_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    controller.layer_nr = layer_nr;

    return;
}
