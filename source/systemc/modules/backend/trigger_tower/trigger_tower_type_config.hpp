/*!
 * @file trigger_tower_type_config.hpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../data_organizer/data_organizer_config.hpp"
#include "../processor_organizer/processor_organizer_config.hpp"
#include "../am_board/am_board_config.hpp"

#include "../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class trigger_tower_type_config
{
    friend class trigger_tower;

private:
    unsigned int layer_nr;
    unsigned int prb_nr;
    unsigned int dtc_per_prb;
    unsigned int AM_boards_per_prb;

public:
    data_organizer_type_config data_organizer;
    processor_organizer_config processor_organizer;
    am_board_config am_board;

    trigger_tower_type_config();

    void set_layer_nr(unsigned int layer_nr);
    unsigned int get_layer_nr() const;
    void set_prb_nr(unsigned int prb_nr);
    unsigned int get_prb_nr() const;
    void set_dtc_per_prb(unsigned int dtc_per_prb);
    unsigned int get_dtc_per_prb() const;
    void set_AM_boards_per_prb(unsigned int AM_boards);
    unsigned int get_AM_boards_per_prb() const;
};
