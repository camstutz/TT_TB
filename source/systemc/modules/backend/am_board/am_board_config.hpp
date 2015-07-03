/*!
 * @file am_board_config.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
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

// *****************************************************************************
/*!
 * @brief
 */
class am_board_config
{
public:
    unsigned int layer_nr;

    am_input_module_config input_module;
    track_finder_config track_finder;
};
