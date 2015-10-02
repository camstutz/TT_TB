/*!
 * @file trigger_tower_type_config.cpp
 * @author Christian Amstutz
 * @date October 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower_type_config.hpp"

// *****************************************************************************
trigger_tower_type_config::trigger_tower_type_config()
{
    set_prb_nr(PRB_NR_PER_TOWER_DEFAULT);
    set_dtc_per_prb(DTC_PER_PRB_DEFAULT);
    set_AM_boards_per_prb(AM_BOARDS_PER_PRB_DEFAULT);

    return;
}

// *****************************************************************************
void trigger_tower_type_config::set_prb_nr(unsigned int prb_nr)
{
    this->prb_nr = prb_nr;

    data_organizer.set_proc_unit_nr(prb_nr);

    return;
}

// *****************************************************************************
unsigned int trigger_tower_type_config::get_prb_nr() const
{
    return prb_nr;
}

// *****************************************************************************
void trigger_tower_type_config::set_dtc_per_prb(unsigned int dtc_per_prb)
{
    this->dtc_per_prb = dtc_per_prb;

    return;
}

// *****************************************************************************
unsigned int trigger_tower_type_config::get_dtc_per_prb() const
{
    return dtc_per_prb;
}

// *****************************************************************************
void trigger_tower_type_config::set_AM_boards_per_prb(unsigned int AM_boards)
{
    this->AM_boards_per_prb = AM_boards;
    processor_organizer.set_processor_output_nr(AM_boards);

    return;
}

// *****************************************************************************
unsigned int trigger_tower_type_config::get_AM_boards_per_prb() const
{
    return AM_boards_per_prb;
}
