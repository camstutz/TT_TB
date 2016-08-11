/*!
 * @file module_address_lookup.cpp
 * @author Christian Amstutz
 * @date August 8, 2016
 *
 * @brief
 */

/*
 *  Copyright (c) 2016 by Christian Amstutz
 */

#include "module_address_lookup_config.hpp"

// *****************************************************************************
void module_address_lookup_config::add_module(hw_address_t hw_address,
        local_address_t local_address, global_address_t global_address)
{
    hw_address_t local_hw_address = hw_address;
    local_hw_address.trigger_tower = 0;

    local_table[hw_address] = local_address;
    global_table[local_address] = global_address;

    return;
}

// *****************************************************************************
void module_address_lookup_config::print_local_table()
{
    std::cout << "Local Table:" << std::endl;

    for(local_table_t::iterator entry_it = local_table.begin();
        entry_it != local_table.end();
        ++entry_it)
    {
        std::cout << entry_it->first << " : " << entry_it->second << std::endl;
    }

    std::cout << std::endl;

    return;
}

// *****************************************************************************
void module_address_lookup_config::print_global_table()
{
    std::cout << "Global Table:" << std::endl;

    for(global_table_t::iterator entry_it = global_table.begin();
        entry_it != global_table.end();
        ++entry_it)
    {
        std::cout << entry_it->first << " : " << entry_it->second << std::endl;
    }

    std::cout << std::endl;

    return;

}
