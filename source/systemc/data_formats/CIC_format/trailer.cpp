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

using namespace CIC;

// *****************************************************************************
trailer::trailer()
{
    trailer_value = 0;

    return;
}

// *****************************************************************************
std::string trailer::get_string() const
{
    return ("[-]");
}

// *****************************************************************************
namespace CIC
{

std::ostream& operator<< (std::ostream& stream, const trailer& trail)
{
    stream << trail.get_string();

    return (stream);
}

} // namespace CIC
