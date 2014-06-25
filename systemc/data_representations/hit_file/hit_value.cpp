/*!
 * @file hit_value.cpp
 * @author Christian Amstutz
 * @date June 17, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_value.hpp"

// *****************************************************************************
hit_value::strip_type hit_value::get_strip()
{
    return(strip);
}

// *****************************************************************************
hit_value::bend_type hit_value::get_bend()
{
    return(bend);
}

// *****************************************************************************
void hit_value::set_strip(strip_type strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
void hit_value::set_bend(bend_type bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
std::string hit_value::to_binary_string(unsigned int value, unsigned int bits)
{
    std::string result("");

    for (unsigned int i=0; i<bits; ++i)
    {
        if (value % 2)
        {
            result.append("1");
        }
        else
        {
            result.append("0");
        }

        value = value / 2;
    }

    return (result);
}
