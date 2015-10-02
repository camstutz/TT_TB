/*!
 * @file trigger_tower_config.hpp
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

#include "trigger_tower_type_config.hpp"
#include "trigger_tower_address.hpp"
#include "../../frontend/sensor_module/sensor_module_address.hpp"

#include <set>

// *****************************************************************************
/*!
 * @brief
 */
class trigger_tower_config
{
    friend class trigger_tower;

public:
    typedef std::vector<data_organizer_config> data_organizer_table_t;

    unsigned int id;
    trigger_tower_address address;
    trigger_tower_type_config type;
    std::set<unsigned int> layers;

    std::vector<unsigned int> DTC_ids;
    std::vector<processor_organizer_config> processor_organizers;

    trigger_tower_config();
    trigger_tower_config(const trigger_tower_type_config& type);

    void add_layer(const unsigned int layer_nr);
    void add_do(const data_organizer_config& new_do);
    data_organizer_config& get_data_organizer(unsigned int DO_id);
    data_organizer_table_t get_data_organizers() const;

private:
    data_organizer_table_t data_organizers;
};
