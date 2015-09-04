/*!
 * @file trigger_tower_config.hpp
 * @author Christian Amstutz
 * @date August 27, 2015
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

#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class trigger_tower_config
{
    friend class trigger_tower;

private:
    std::vector<data_organizer_config> data_organizers;

public:
    unsigned int id;
    trigger_tower_address address;
    //std::string pattern_bank_file;
    trigger_tower_type_config type;

    std::vector<unsigned int> DTC_ids;
    std::vector<processor_organizer_config> processor_organizers;

    trigger_tower_config();
    trigger_tower_config(const trigger_tower_type_config& type);

    void add_do(const data_organizer_config& new_do);
    data_organizer_config& get_data_organizer(unsigned int DO_id);
};
