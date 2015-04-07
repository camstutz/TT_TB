/*!
 * @file trailer.hpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>

// *****************************************************************************
namespace CIC
{

class trailer
{
public:
    typedef unsigned int trailer_value_t;

    trailer();

    std::string get_string() const;

private:
    trailer_value_t trailer_value;
};

} // namespace CIC
