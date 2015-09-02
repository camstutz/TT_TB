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

#pragma once

#include "hit_processor_one_layer_config.hpp"

#include "../../../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class hit_processor_config
{
    friend class hit_processor;

private:
    unsigned int layer_nr;

public:
    hit_processor_one_layer_config hit_processor_one_layer;

    hit_processor_config();

    void set_layer_nr(unsigned int layer_nr);
};
