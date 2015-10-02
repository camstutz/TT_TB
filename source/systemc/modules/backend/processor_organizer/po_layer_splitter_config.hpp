/*!
 * @file po_layer_splitter_config.hpp
 * @author Christian Amstutz
 * @date October 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../TT_configuration/prbf_module_address.hpp"

#include <map>
#include <set>

// *****************************************************************************
/*!
 * @brief
 */
class po_layer_splitter_config
{
public:
    typedef std::map<prbf_module_address, unsigned int> layer_lookup_table_t;

    std::set<unsigned int> layers;

    unsigned int trigger_tower_id;
    layer_lookup_table_t layer_lookup_table;

    void add_layer(const unsigned int layer_nr);
};
