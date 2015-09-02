/*!
 * @file am_board_config.hpp
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

#include "am_input_module/am_input_module_config.hpp"
#include "track_finder/track_finder_config.hpp"

#include "../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class am_board_config
{
friend class am_board;

private:
    unsigned int layer_nr;

public:
    am_input_module_config input_module;
    track_finder_config track_finder;

    am_board_config();

    void set_layer_nr(unsigned int layer_nr);
};
