/*!
 * @file hit_value.hpp
 * @author Christian Amstutz
 * @date June 24, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>

#include "hit_value.hpp"

/*!
 * @brief
 */
class hit_value_mpa : public hit_value
{
public:
    typedef unsigned int bx_offset_type;
    typedef unsigned int pixel_type;

    static const unsigned int bx_pos = 0;
    static const unsigned int bx_bits = 1;
    static const unsigned int strip_pos = bx_pos + bx_bits;
    static const unsigned int strip_bits = 8;
    static const unsigned int bend_pos = strip_pos + strip_bits;
    static const unsigned int bend_bits = 5;
    static const unsigned int pixel_pos = bend_pos + bend_bits;
    static const unsigned int pixel_bits = 4;
    static const unsigned int binary_value_length = pixel_pos + pixel_bits;

    hit_value_mpa(std::string binary_value);
    hit_value_mpa(bx_offset_type bx_offset, strip_type strip, bend_type bend,
            pixel_type pixel);
    ~hit_value_mpa() {};

    std::string get_string();
    std::string get_string_binary();
    bx_offset_type get_bx_offset();
    pixel_type get_pixel();

private:
    bx_offset_type bx_offset;
    pixel_type pixel;

    void set_value(std::string binary_value);
    void set_bx_offset(bx_offset_type bx_offset);
    void set_pixel(pixel_type pixel);
};
