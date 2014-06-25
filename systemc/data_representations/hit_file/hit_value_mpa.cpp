/*!
 * @file hit_value_mpa.cpp
 * @author Christian Amstutz
 * @date June 24, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit_value_mpa.hpp"

// *****************************************************************************
hit_value_mpa::hit_value_mpa(std::string binary_value)
{
    set_value(binary_value);

    return;
}

// *****************************************************************************
hit_value_mpa::hit_value_mpa(bx_offset_type bx_offset, strip_type strip,
        bend_type bend, pixel_type pixel)
{
    set_bx_offset(bx_offset);
    set_bend(bend);
    set_strip(strip);
    set_pixel(pixel);

    return;
}

// *****************************************************************************
hit_value_mpa::bx_offset_type hit_value_mpa::get_bx_offset()
{
    return(bx_offset);
}

// *****************************************************************************
hit_value_mpa::pixel_type hit_value_mpa::get_pixel()
{
    return(pixel);
}

// *****************************************************************************
void hit_value_mpa::set_value(std::string binary_value)
{
    try
    {
        if (binary_value.length() != binary_value_length)
        {
            throw true;
        }

        std::string bx_string = binary_value.substr(bx_pos, bx_bits);
        set_bx_offset( std::strtol(bx_string.c_str(), NULL, 2) );
        std::string strip_string = binary_value.substr(strip_pos, strip_bits);
        set_strip( std::strtol(strip_string.c_str(), NULL, 2) );
        std::string bend_string = binary_value.substr(bend_pos, bend_bits);
        set_bend( std::strtol(bend_string.c_str(), NULL, 2) );
        std::string pixel_string = binary_value.substr(pixel_pos, pixel_bits);
        set_pixel( std::strtol(pixel_string.c_str(), NULL, 2) );
    }
    catch (bool error)
    {
        std::cerr << "Error with binary format of hit_value_mpa." << std::endl;
    }

    return;
}

// *****************************************************************************
std::string hit_value_mpa::get_string()
{
    std::stringstream result;

    result << "[";
    result << "BX=" << get_bx_offset();
    result << "S=" << get_strip();
    result << "B=" << get_bend();
    result << "P=" << get_pixel();
    result << "]";

    return (result.str());
}

// *****************************************************************************
std::string hit_value_mpa::get_string_binary()
{
    std::string result("");

    result.append(to_binary_string(get_bx_offset(), bx_bits));
    result.append(to_binary_string(get_bend(), bend_bits));
    result.append(to_binary_string(get_strip(), strip_bits));
    result.append(to_binary_string(get_pixel(), pixel_bits));

    return (result);
}

// *****************************************************************************
void hit_value_mpa::set_bx_offset(bx_offset_type bx_offset)
{
    this->bx_offset = bx_offset;

    return;
}

// *****************************************************************************
void hit_value_mpa::set_pixel(pixel_type pixel)
{
    this->pixel = pixel;

    return;
}
