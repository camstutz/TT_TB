/*!
 * @file hit_procesor_config.hpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_processor_config.hpp"

// *****************************************************************************
hit_processor_config::hit_processor_config()
{
    set_layer_nr(LAYER_DEFAULT);

    return;
}

// *****************************************************************************
void hit_processor_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    return;
}

