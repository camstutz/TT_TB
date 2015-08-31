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

#include "data_organizer/data_organizer_config.hpp"
#include "processor_organizer/processor_organizer_config.hpp"
#include "am_board/am_board_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class trigger_tower_type_config
{
public:
    unsigned int layer_nr;
    unsigned int prb_nr;
    unsigned int dtc_per_prb;
    unsigned int AM_boards_per_prb;

    data_organizer_type_config data_organizer;
    processor_organizer_config processor_organizer;
    am_board_config am_board;
};
