/*!
 * @file hit_procesor_config.hpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "hit_processor_one_layer_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class hit_processor_config
{
public:
    unsigned int layer_nr;

    hit_processor_one_layer_config hit_processor_one_layer;
};
