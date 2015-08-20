/*!
 * @file sensor_module_address.cpp
 * @author Christian Amstutz
 * @date August 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sensor_module_address.hpp"

// *****************************************************************************
sensor_module_address::sensor_module_address() :
        layer(0),
        ladder(0),
        module(0)
{}

// *****************************************************************************
sensor_module_address::sensor_module_address(unsigned int layer,
        unsigned int ladder, unsigned int module) :
        layer(layer),
        ladder(ladder),
        module(module)
{}

// *****************************************************************************
bool sensor_module_address::operator== (const sensor_module_address& rhs) const
{
    bool equal = true;

    equal &= (layer == rhs.layer);
    equal &= (ladder == rhs.ladder);
    equal &= (module == rhs.module);

    return equal;
}

// *****************************************************************************
bool sensor_module_address::operator< (const sensor_module_address& rhs) const
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
            if(module < rhs.module)
            {
                return true;
            }
        }
    }

    return false;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, sensor_module_address const &v)
{
    os << "lay=" << v.layer;
    os << "lad=" << v.ladder;
    os << "mod=" << v.module;

    return os;
};
