/*!
 * @file local_module_address.cpp
 * @author Christian Amstutz
 * @date October 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "local_module_address.hpp"

// *****************************************************************************
local_module_address::local_module_address() :
        layer(0),
        ladder(0),
        module(0)
{}

// *****************************************************************************
local_module_address::local_module_address(const unsigned int layer,
        const unsigned int ladder, const unsigned int module) :
        layer(layer),
        ladder(ladder),
        module(module)
{}

// *****************************************************************************
bool local_module_address::operator== (const local_module_address& rhs) const
{
    bool equal = true;

    equal &= (layer == rhs.layer);
    equal &= (ladder == rhs.ladder);
    equal &= (module == rhs.module);

    return equal;
}

// *****************************************************************************
bool local_module_address::operator< (const local_module_address& rhs) const
{
    if (layer < rhs.layer)
    {
        return true;
    }

    if (layer == rhs.layer)
    {
        if (ladder < rhs.ladder)
        {
            return true;
        }

        if (ladder == rhs.ladder)
        {
            if (module < rhs.module)
            {
                return true;
            }
        }
    }

    return false;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, local_module_address const &v)
{
    os << "LocalLay=" << v.layer;
    os << ",LocalLad=" << v.ladder;
    os << ",LocalMod=" << v.module;

    return os;
};
