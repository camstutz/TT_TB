/*!
 * @file po_layer_splitter_config.cpp
 * @author Christian Amstutz
 * @date October 6, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "po_layer_splitter_config.hpp"

//// *****************************************************************************
//void po_layer_splitter_config::add_module(const prbf_module_address& rel_address,
//        const layer_t layer)
//{
//    layer_lookup_table[rel_address] = layer;
//    add_layer(layer);
//
//    return;
//}

// *****************************************************************************
po_layer_splitter_config::layer_t po_layer_splitter_config::get_layer_nr() const
{
    return layers.size();
}

// *****************************************************************************
unsigned int po_layer_splitter_config::get_layer_pos(const layer_t layer) const
{
    unsigned int layer_pos = 0;
    for (typename std::set<layer_t>::iterator layer_it = layers.begin();
         layer_it != layers.end();
         ++layer_it)
    {
        if (*layer_it == layer)
        {
            return layer_pos;
        }

        ++layer_pos;
    }

    return 0;
}

//// *****************************************************************************
//std::pair<bool, unsigned int> po_layer_splitter_config::get_layer(
//        const prbf_module_address& rel_address) const
//{
//    std::pair<bool, unsigned int> return_layer;
//    layer_lookup_table_t::const_iterator layer_it = layer_lookup_table.find(rel_address);
//
//    if (layer_it != layer_lookup_table.end())
//    {
//        return_layer.first = true;
//        return_layer.second = layer_it->second;
//    }
//    else
//
//    {
//        return_layer.first = false;
//        return_layer.second = 0;
//    }
//
//    return return_layer;
//}

// *****************************************************************************
unsigned int po_layer_splitter_config::get_trigger_tower_id() const
{
    return trigger_tower_id;
}

//// *****************************************************************************
//void po_layer_splitter_config::print_layer_table(sc_module_name _name) const
//{
//    std::cout << "Layer Translation table of " << _name
//              << " sized " << layer_lookup_table.size() << std::endl;
//    std::cout << "-----------------------------------------------" << std::endl;
//    for (po_layer_splitter_config::layer_lookup_table_t::const_iterator layer_table_line = layer_lookup_table.begin();
//         layer_table_line != layer_lookup_table.end();
//         ++layer_table_line)
//    {
//        std::cout << layer_table_line->first
//                  << " --> "
//                  << layer_table_line->second
//                  << std::endl;
//    }
//
//    return;
//}

// *****************************************************************************
void po_layer_splitter_config::add_layer(const unsigned int layer_nr)
{
    layers.insert(layer_nr);

    return;
}
