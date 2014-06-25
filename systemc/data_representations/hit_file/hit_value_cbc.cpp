/*!
 * @file hit_value_cbc.cpp
 * @author Christian Amstutz
 * @date June 24, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_value_cbc.hpp"

// *****************************************************************************
hit_value_cbc::hit_value_cbc(std::string binary_value)
{
    set_value(binary_value);

    return;
}

// *****************************************************************************
hit_value_cbc::hit_value_cbc(strip_type strip, bend_type bend)
{
    set_strip(strip);
    set_bend(bend);

    return;
}

// *****************************************************************************
std::string hit_value_cbc::get_string()
{
    std::stringstream result;

    result << "[";
    result << "S=" << get_strip();
    result << "B=" << get_bend();
    result << "]";

    return (result.str());
}

// *****************************************************************************
std::string hit_value_cbc::get_string_binary()
{
    std::string result("");

    result.append(to_binary_string(get_bend(), bend_bits));
    result.append(to_binary_string(get_strip(), strip_bits));

    return (result);
}

// *****************************************************************************
void hit_value_cbc::set_value(std::string binary_value)
{
    try
    {
        if (binary_value.length() != binary_value_length)
        {
            throw true;
        }

        std::string strip_string = binary_value.substr(strip_pos, strip_bits);
        set_strip( std::strtol(strip_string.c_str(), NULL, 2) );
        std::string bend_string = binary_value.substr(bend_pos, bend_bits);
        set_bend( std::strtol(bend_string.c_str(), NULL, 2) );
    }
    catch (bool error)
    {
        std::cerr << "Error with binary format of hit_value_cbc." << std::endl;
    }

    return;
}
