/*!
 * @file pattern_memory_config.hpp
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

#include "../pattern_bank/pattern_bank.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class pattern_memory_config
{
public:
    unsigned int layer_nr;
    pattern_bank* ptrn_bank;
};
