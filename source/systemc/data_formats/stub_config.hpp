/*!
 * @file stub_config.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "stub_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class stub_config
{
public:
    unsigned int valid_bits;
    unsigned int bx_bits;
    unsigned int fechip_bits;
    unsigned int strip_bits;
    unsigned int bend_bits;
    unsigned int pixel_bits;

    bool operator== (const stub_config &v) const;
};
