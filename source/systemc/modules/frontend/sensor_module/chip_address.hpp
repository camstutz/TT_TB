/*!
 * @file chip_address.hpp
 * @author Christian Amstutz
 * @date August 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <ostream>

// *****************************************************************************
/*!
 * @brief
 */
class chip_address
{
public:
    unsigned int layer;
    unsigned int ladder;
    unsigned int module;
    unsigned int segment;
    unsigned int chip;

    chip_address();
    chip_address(unsigned int layer, unsigned int ladder, unsigned int module, unsigned int segment, unsigned int chip);

    bool operator== (const chip_address& rhs) const;
    bool operator< (const chip_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, chip_address const &v);
};
