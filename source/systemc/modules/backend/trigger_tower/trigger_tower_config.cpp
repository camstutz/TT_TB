/*!
 * @file trigger_tower_config.cpp
 * @author Christian Amstutz
 * @date September 11, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower_config.hpp"

// *****************************************************************************
trigger_tower_config::trigger_tower_config()
{}

// *****************************************************************************
trigger_tower_config::trigger_tower_config(const trigger_tower_type_config& type)
{
    this->type = type;

    for (unsigned int i = 0; i < type.get_prb_nr(); ++i)
    {
        processor_organizer_config new_po;
        new_po = type.processor_organizer;
        new_po.demultiplexer.bx_offset = i;
        processor_organizers.push_back(new_po);
    }

    return;
}

// *****************************************************************************
void trigger_tower_config::add_do(const data_organizer_config& new_do)
{
    data_organizers.push_back(new_do);
    for (std::vector<processor_organizer_config>::iterator po_it = processor_organizers.begin();
         po_it != processor_organizers.end();
         ++po_it)
    {
        po_it->add_do();
    }

    return;
}

// *****************************************************************************
data_organizer_config& trigger_tower_config::get_data_organizer(
        unsigned int DO_id)
{
    return data_organizers[DO_id];
}

// *****************************************************************************
trigger_tower_config::data_organizer_table_t
        trigger_tower_config::get_data_organizers() const
{
    return data_organizers;
}
