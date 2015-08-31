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
std::vector<chip_address> sensor_module_address::get_chips (
        const unsigned int nr_segments, const unsigned int nr_chips) const
{
    std::vector<chip_address> chips;
    for (unsigned int segment_id = 0; segment_id < nr_segments; ++segment_id)
    {
        for (unsigned int chip_id = 0; chip_id < nr_chips; ++chip_id)
        {
            chips.push_back(chip_address(layer, ladder, module, segment_id, chip_id));
        }
    }

    return chips;
}

// *****************************************************************************
std::vector<chip_address> sensor_module_address::get_chips (
        const sensor_module_type_config& sensor_mod_config) const
{
    return get_chips(sensor_mod_config.side_count,
            sensor_mod_config.fe_chip_per_side);
}

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
