/*!
 * @file sector_info.cpp
 * @author Christian Amstutz
 * @date September 30, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sector_info.hpp"

// *****************************************************************************
sector_info::sector_info() :
        id(0),
        eta(0),
        phi(0)
{}

// *****************************************************************************
sector_info::sector_info(const unsigned int id, const unsigned int eta,
        const unsigned int phi) :
        id(id),
        eta(eta),
        phi(phi)
{}


// *****************************************************************************
bool sector_info::operator== (const sector_info& rhs) const
{
    bool equal = true;

    equal &= (id == rhs.id);
    equal &= (eta == rhs.eta);
    equal &= (phi == rhs.phi);

    return equal;
}

// *****************************************************************************
bool sector_info::operator< (const sector_info& rhs) const
{
    if (eta < rhs.eta)
    {
        return true;
    }

    if (eta == rhs.eta)
    {
        if (phi < rhs.phi)
        {
            return true;
        }
    }

    return false;
}

// *****************************************************************************
void sector_info::add_modules(const sensor_module_address& module_address)
{
    std::pair<layer_set_t::iterator, bool> inserted_layer = layers.insert(module_address.layer);
    if (inserted_layer.second)
    {
        ladders[module_address.layer] = std::set<ladder_t>();
    }

    std::pair<std::set<ladder_t>::iterator, bool> inserted_ladder = ladders[module_address.layer].insert(module_address.ladder);
    if (inserted_ladder.second)
    {
        modules[module_address.layer][module_address.ladder] = std::set<module_t>();
    }

    modules[module_address.layer][module_address.ladder].insert(module_address.module);

    return;
}

// *****************************************************************************
std::pair<bool, local_module_address> sector_info::get_local_address(
        sensor_module_address global_address)
{
    std::pair<bool, local_module_address> found_address;

    // Does information about the module exist?
    if (modules[global_address.layer][global_address.ladder].count(global_address.module))
    {
        found_address.first = true;

        unsigned int local_ladder = 0;
        for (std::set<ladder_t>::iterator ladder_it = ladders[global_address.layer].begin();
             ladder_it != ladders[global_address.layer].end();
             ++ladder_it)
        {
            if (*ladder_it == global_address.ladder)
            {
                break;
            }
            ++local_ladder;
        }

        unsigned int local_module = 0;
        for (std::set<module_t>::iterator module_it = modules[global_address.layer][global_address.ladder].begin();
             module_it != modules[global_address.layer][global_address.ladder].end();
             ++module_it)
        {
            if (*module_it == global_address.module)
            {
                break;
            }
            ++local_module;
        }

        local_module_address local_address(global_address.layer, local_ladder, local_module);
        found_address.second = local_address;
    }
    else
    {
        found_address.first = false;
        found_address.second = local_module_address();
    }

    return  found_address;
}

// *****************************************************************************
void sector_info::print_layers()
{
    std::cout << "Layers in sector " << id << " (" << layers.size() << ")" <<std::endl;
    for (layer_set_t::iterator layer_it = layers.begin();
         layer_it != layers.end();
         ++layer_it)
    {
        std::cout << *layer_it << ", ";
    }
    std::cout << std::endl;

    return;
}

// *****************************************************************************
void sector_info::print_ladders()
{
    std::cout << "Ladders in sector " << id << std::endl;
    for (layer_set_t::iterator layer_it = layers.begin();
         layer_it != layers.end();
         ++layer_it)
    {
        std::cout << "Layer " << *layer_it << ": ";

        for (std::set<ladder_t>::iterator ladder_it = ladders[*layer_it].begin();
             ladder_it != ladders[*layer_it].end();
             ++ladder_it)
        {
            std::cout << *ladder_it << ", ";
        }

        std::cout << std::endl;
    }

    return;
}

// *****************************************************************************
void sector_info::print_modules()
{
    std::cout << "Modules in sector " << id << std::endl;
    for (layer_set_t::iterator layer_it = layers.begin();
         layer_it != layers.end();
         ++layer_it)
    {
        std::cout << "Layer " << *layer_it << ": ";

        for (std::set<ladder_t>::iterator ladder_it = ladders[*layer_it].begin();
             ladder_it != ladders[*layer_it].end();
             ++ladder_it)
        {
            for (std::set<module_t>::iterator module_it = modules[*layer_it][*ladder_it].begin();
                 module_it != modules[*layer_it][*ladder_it].end();
                 ++module_it)
            {
                std::cout << (100* (*ladder_it)) + (*module_it) << ", ";
            }
        }

        std::cout << std::endl;
    }

    return;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, sector_info const &v)
{
    os << "id=" << v.id;
    os << ",eta=" << v.eta;
    os << ",phi=" << v.phi;

    return os;
};
