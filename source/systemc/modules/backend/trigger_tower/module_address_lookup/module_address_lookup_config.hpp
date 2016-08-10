/*!
 * @file module_address_lookup_config.hpp
 * @author Christian Amstutz
 * @date August 8, 2016
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2016 by Christian Amstutz
 */

#pragma once

#include "../../../../data_formats/prbf/PRBF.hpp"
#include "../../../../modules/frontend/sensor_module/sensor_module_address.hpp"
#include "../../../../TT_configuration/local_module_address.hpp"
#include "../../../../TT_configuration/prbf_module_address.hpp"

#include <map>

// *****************************************************************************
/*!
 * @brief
 */
class module_address_lookup_config
{
    friend class module_address_lookup;

    typedef prbf_module_address hw_address_t;
    typedef local_module_address local_address_t;
    typedef sensor_module_address global_address_t;

private:
    typedef std::map<hw_address_t, local_address_t> local_table_t;
    typedef std::map<local_address_t, global_address_t> global_table_t;

    local_table_t local_table;
    global_table_t global_table;

public:
    void add_module(hw_address_t hw_address, local_address_t local_address, global_address_t global_address);

    void print_local_table();
    void print_global_table();
};
