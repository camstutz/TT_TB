/*!
 * @file po_layer_splitter_config.hpp
 * @author Christian Amstutz
 * @date September 11, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../TT_configuration/local_module_address.hpp"

#include <map>

// *****************************************************************************
/*!
 * @brief
 */
class po_layer_splitter_config
{
public:
    typedef std::map<local_module_address, unsigned int> layer_lookup_table_t;

    unsigned int layer_nr;

    unsigned int trigger_tower_id;
    layer_lookup_table_t layer_lookup_table;
};
