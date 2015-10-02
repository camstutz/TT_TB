/*!
 * @file po_layer_splitter_config.cpp
 * @author Christian Amstutz
 * @date October 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "po_layer_splitter_config.hpp"

// *****************************************************************************
void po_layer_splitter_config::add_layer(const unsigned int layer_nr)
{
    layers.insert(layer_nr);

    return;
}
