/*!
 * @file trigger_tower_address.hpp
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

#include <string>
#include <sstream>
#include <ostream>

// *****************************************************************************
/*!
 * @brief
 */
class trigger_tower_address
{
public:
    int phi;
    int z;

    trigger_tower_address();
    trigger_tower_address(int phi, int z);

    bool operator== (const trigger_tower_address& rhs) const;
    bool operator< (const trigger_tower_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, trigger_tower_address const &v);
};
