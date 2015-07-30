/*!
 * @file stub_config.cpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_config.hpp"

// *****************************************************************************
bool stub_config::operator== (const stub_config &v) const
{
    bool equal = true;

    equal &= (valid_bits==v.valid_bits);
    equal &= (bx_bits==v.bx_bits);
    equal &= (fechip_bits==v.fechip_bits);
    equal &= (strip_bits==v.strip_bits);
    equal &= (bend_bits==v.bend_bits);
    equal &= (pixel_bits==v.pixel_bits);

    return equal;
}
