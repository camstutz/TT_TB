/*!
 * @file trigger_tower_config.cpp
 * @author Christian Amstutz
 * @date September 2, 2015
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
