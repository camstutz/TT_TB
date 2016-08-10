/*!
 * @file module_address_lookup.hpp
 * @author Christian Amstutz
 * @date August 8, 2016
 *
 * @brief
 */

/*
 *  Copyright (c) 2016 by Christian Amstutz
 */

#pragma once

#include "module_address_lookup_config.hpp"

#include <map>
#include <utility>

class module_address_lookup
{
private:
    const module_address_lookup_config configuration;

public:
    typedef module_address_lookup_config::hw_address_t hw_address_t;
    typedef module_address_lookup_config::local_address_t local_address_t;
    typedef module_address_lookup_config::global_address_t global_address_t;

    module_address_lookup(module_address_lookup_config config);

    std::pair<bool, local_address_t> get_local_address(hw_address_t hw_address);
    std::pair<bool, global_address_t> get_global_address(hw_address_t hw_address);
    std::pair<bool, global_address_t> get_global_address(local_address_t local_address);
};
