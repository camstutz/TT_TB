/*!
 * @file trigger_tower_address.cpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower_address.hpp"

// *****************************************************************************
trigger_tower_address::trigger_tower_address() :
        phi(0),
        z(0)
{}

// *****************************************************************************
trigger_tower_address::trigger_tower_address(int phi, int z) :
        phi(phi),
        z(z)
{}


// *****************************************************************************
bool trigger_tower_address::operator== (const trigger_tower_address& rhs) const
{
    bool equal = true;

    equal &= (phi == rhs.phi);
    equal &= (z == rhs.z);

    return equal;
}

// *****************************************************************************
bool trigger_tower_address::operator< (const trigger_tower_address& rhs) const
{
    if (phi < rhs.phi)
    {
        return true;
    }

    if (phi == rhs.phi)
    {
        if (z < rhs.z)
        {
            return true;
        }
    }

    return false;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, trigger_tower_address const &v)
{
    os << "phi=" << v.phi;
    os << "z=" << v.z;

    return os;
};
