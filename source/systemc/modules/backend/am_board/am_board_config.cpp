/*!
 * @file am_board_config.cpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_board_config.hpp"

// *****************************************************************************
am_board_config::am_board_config()
{
    set_layer_nr(LAYER_DEFAULT);

    return;
}

// *****************************************************************************
void am_board_config::set_layer_nr(unsigned int layer_nr)
{
    this->layer_nr = layer_nr;

    input_module.set_layer_nr(layer_nr);
    track_finder.set_layer_nr(layer_nr);

    return;
}
