/*!
 * @file sc_map_key.cpp
 * @author Christian Amstutz
 * @date May 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_key.hpp"

//******************************************************************************
bool sc_map_key::Comperator::operator()(const sc_map_key& lhs,
        const sc_map_key& rhs) const
{
    return (lhs < rhs);
}

//******************************************************************************
bool sc_map_key::operator!=(const sc_map_key& other_key) const
{
    return *this == other_key;
}

//******************************************************************************
bool sc_map_key::operator>(const sc_map_key& other_key) const
{
    return other_key < *this;
}

//******************************************************************************
bool sc_map_key::operator<=(const sc_map_key& other_key) const
{
    return !(*this > other_key);
}

//******************************************************************************
bool sc_map_key::operator>=(const sc_map_key& other_key) const
{
    return !(*this < other_key);
}

//******************************************************************************
std::ostream& operator<< (std::ostream &out, const sc_map_key &key)
{
    out << key.get_string();

    return out;
}
