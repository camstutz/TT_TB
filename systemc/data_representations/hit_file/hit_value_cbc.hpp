/*!
 * @file hit_value_cbc.hpp
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

#include "hit_value.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

/*!
 * @brief
 */
class hit_value_cbc : public hit_value
{
public:
    static const unsigned int strip_pos = 0;
    static const unsigned int strip_bits = 8;
    static const unsigned int bend_pos = strip_pos + strip_bits;
    static const unsigned int bend_bits = 5;
    static const unsigned int binary_value_length = bend_pos + bend_bits;

    hit_value_cbc(std::string binary_value);
    hit_value_cbc(strip_type strip, bend_type bend);
    ~hit_value_cbc() {};

    std::string get_string();
    std::string get_string_binary();

private:
    void set_value(std::string binary_value);
};
