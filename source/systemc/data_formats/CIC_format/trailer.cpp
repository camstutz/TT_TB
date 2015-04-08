/*!
 * @file trailer.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trailer.hpp"

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
trailer::trailer()
{
    trailer_value = 0;

    return;
}

// *****************************************************************************
bool trailer::operator== (const trailer& rhs) const
{
    bool equal = true;

    equal &= (rhs.trailer_value == trailer_value);

    return (equal);
}

// *****************************************************************************
std::string trailer::get_string() const
{
    return ("[-]");
}

// *****************************************************************************
std::ostream& operator<< (std::ostream& stream, const trailer& trail)
{
    stream << trail.get_string();

    return (stream);
}

// *****************************************************************************
} // namespace CIC
