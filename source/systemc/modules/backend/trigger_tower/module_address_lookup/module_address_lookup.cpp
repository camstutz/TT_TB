/*!
 * @file module_address_lookup.cpp
 * @author Christian Amstutz
 * @date August 10, 2016
 *
 * @brief
 */

/*
 *  Copyright (c) 2016 by Christian Amstutz
 */

#include "module_address_lookup.hpp"

// *****************************************************************************
module_address_lookup::module_address_lookup(module_address_lookup_config config) :
        configuration(config)
{}

// *****************************************************************************
std::pair<bool, module_address_lookup::local_address_t>
        module_address_lookup::get_local_address(hw_address_t hw_address)
{
    std::pair<bool, module_address_lookup::local_address_t> result;

    module_address_lookup_config::local_table_t::const_iterator search = configuration.local_table.find(hw_address);
    if(search != configuration.local_table.end())
    {
        result.first = true;
        result.second = search->second;
    }
    else
    {
        result.first = false;
        result.second = local_address_t();
    }

    return result;
}

// *****************************************************************************
std::pair<bool, module_address_lookup::global_address_t>
        module_address_lookup::get_global_address(hw_address_t hw_address)
{
    std::pair<bool, module_address_lookup::global_address_t> result;

    std::pair<bool, local_address_t> local_address = get_local_address(hw_address);
    if (local_address.first)
    {
        result = get_global_address(local_address.second);
    }
    else
    {
        result.first = false;
        result.second = global_address_t();
    }

    return result;
}

// *****************************************************************************
std::pair<bool, module_address_lookup::global_address_t>
        module_address_lookup::get_global_address(local_address_t local_address)
{
    std::pair<bool, module_address_lookup::global_address_t> result;

    module_address_lookup_config::global_table_t::const_iterator search = configuration.global_table.find(local_address);
    if(search != configuration.global_table.end())
    {
        result.first = true;
        result.second = search->second;
    }
    else
    {
        result.first = false;
        result.second = global_address_t();
    }

    return result;
}
