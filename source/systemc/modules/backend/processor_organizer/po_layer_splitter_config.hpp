/*!
 * @file po_layer_splitter_config.hpp
 * @author Christian Amstutz
 * @date October 6, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../TT_configuration/prbf_module_address.hpp"

#include <systemc.h>

#include <map>
#include <set>
#include <utility>

// *****************************************************************************
/*!
 * @brief
 */
class po_layer_splitter_config
{
public:
    typedef std::map<prbf_module_address, unsigned int> layer_lookup_table_t;
    typedef unsigned int layer_t;

    void add_module(const prbf_module_address& rel_address, const layer_t layer);
    unsigned int get_layer_nr() const;
    unsigned int get_layer_pos(const layer_t layer) const;
    std::pair<bool, layer_t> get_layer(const prbf_module_address& rel_address) const;
    unsigned int get_trigger_tower_id() const;

    void print_layer_table(sc_module_name _name) const;

private:
    std::set<layer_t> layers;

    unsigned int trigger_tower_id;
    layer_lookup_table_t layer_lookup_table;

    void add_layer(const layer_t layer_nr);
};
