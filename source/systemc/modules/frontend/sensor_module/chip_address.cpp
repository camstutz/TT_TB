/*!
 * @file chip_address.cpp
 * @author Christian Amstutz
 * @date August 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "chip_address.hpp"

// *****************************************************************************
chip_address::chip_address() :
        layer(0),
        ladder(0),
        module(0),
        segment(0),
        chip(0)
{}

// *****************************************************************************
chip_address::chip_address(unsigned int layer,
        unsigned int ladder, unsigned int module, unsigned segment,
        unsigned chip) :
        layer(layer),
        ladder(ladder),
        module(module),
        segment(segment),
        chip(chip)
{}

// *****************************************************************************
bool chip_address::operator== (const chip_address& rhs) const
{
    bool equal = true;

    equal &= (layer == rhs.layer);
    equal &= (ladder == rhs.ladder);
    equal &= (module == rhs.module);
    equal &= (segment == rhs.segment);
    equal &= (chip == rhs.chip);

    return equal;
}

// *****************************************************************************
bool chip_address::operator< (const chip_address& rhs) const
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

            if (module == rhs.module)
            {
                if(segment < rhs.segment)
                {
                    return true;
                }

                if (segment == rhs.segment)
                {
                    if(chip < rhs.chip)
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, chip_address const &v)
{
    os << "lay=" << v.layer;
    os << "lad=" << v.ladder;
    os << "mod=" << v.module;
    os << "seg=" << v.segment;
    os << "chp=" << v.chip;

    return os;
};
