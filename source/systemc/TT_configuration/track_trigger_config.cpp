/*!
 * @file track_trigger_config.cpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "track_trigger_config.hpp"

// *****************************************************************************
std::vector<sensor_module_address> track_trigger_config::get_module_addresses() const
{
    std::vector<sensor_module_address> module_addresses;
    for (typename std::vector<sensor_module_config>::const_iterator module_config_it = sensor_modules.begin();
         module_config_it != sensor_modules.end();
         module_config_it++)
    {
        module_addresses.push_back(module_config_it->address);
    }

    return module_addresses;
}

// *****************************************************************************
std::vector<chip_address> track_trigger_config::get_chip_addresses() const
{
    std::vector<chip_address> chip_addresses;
    for (std::vector<sensor_module_config>::const_iterator module_config_it = sensor_modules.begin();
         module_config_it != sensor_modules.end();
         module_config_it++)
    {
        sensor_module_address module_address = module_config_it->address;
        std::vector<chip_address> new_chips = module_address.get_chips(*(module_config_it->type) );
        chip_addresses.insert(chip_addresses.end(), new_chips.begin(), new_chips.end());
    }

    return chip_addresses;
}

// *****************************************************************************
std::vector<trigger_tower_address> track_trigger_config::get_trigger_tower_addresses() const
{
    std::vector<trigger_tower_address> tower_addresses;
    for (std::vector<trigger_tower_config>::const_iterator tower_config_it = trigger_towers.begin();
         tower_config_it != trigger_towers.end();
         tower_config_it++)
    {
        tower_addresses.push_back(tower_config_it->address);
    }

    return tower_addresses;
}
