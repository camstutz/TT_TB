/*!
 * @file hit_buffer_config.cpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_buffer_config.hpp"

// *****************************************************************************
hit_buffer_config::hit_buffer_config()
{
    set_layer_nr(LAYER_DEFAULT);
    set_SS_width_bit(SS_WIDTH_BIT_DEFAULT);

    return;
}

// *****************************************************************************
void hit_buffer_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    hit_buffer_write_ctrl.layer_nr = layer_nr;
    hit_buffer_lookup_ctrl.layer_nr = layer_nr;
    hit_buffer_output_ctrl.layer_nr = layer_nr;

    return;
}

// *****************************************************************************
void hit_buffer_config::set_SS_width_bit(unsigned int SS_width_bit)
{
    this->SS_width_bit = SS_width_bit;

    return;
}
