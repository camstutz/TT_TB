/*!
 * @file am_chip_config.hpp
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

#include "am_chip_write_ctrl_config.hpp"
#include "../pattern_bank/pattern_bank.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class am_chip_config
{
public:
    unsigned int layer_nr;

    am_chip_write_ctrl_config write_ctrl;
};
