/*!
 * @file hit_value.hpp
 * @author Christian Amstutz
 * @date June 16, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>

/*!
 * @brief
 */
class hit_value
{
public:
    typedef unsigned int strip_type;
    typedef int bend_type;

    virtual ~hit_value() {};

    virtual std::string get_string() =0;
    virtual std::string get_string_binary() =0;
    strip_type get_strip();
    bend_type get_bend();

protected:
    strip_type strip;
    bend_type bend;

    virtual void set_value(std::string binary_value) =0;
    void set_strip(strip_type strip);
    void set_bend(bend_type bend);

    static std::string to_binary_string(unsigned int value, unsigned int bits);
};
