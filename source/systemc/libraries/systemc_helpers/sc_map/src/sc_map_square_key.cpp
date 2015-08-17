/*!
 * @file sc_map_square_key.cpp
 * @author Christian Amstutz
 * @date June 16, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "../include/sc_map_square_key.hpp"

//******************************************************************************
sc_map_square_key::sc_map_square_key() :
        Y(sc_map_regular_key::default_start_id),
        X(sc_map_regular_key::default_start_id)
{}

//******************************************************************************
sc_map_square_key::sc_map_square_key(const index_type& Y, const index_type& X) :
        Y(Y),
        X(X)
{}

//******************************************************************************
std::string sc_map_square_key::get_string() const
{
    std::stringstream collection_stream;
    collection_stream << Y;
    collection_stream << sc_map::key_sub_separator_char;
    collection_stream << X;

    return collection_stream.str();
}

//******************************************************************************
bool sc_map_square_key::operator==(const sc_map_key& other_key) const
{
    const sc_map_square_key* other_key_square =
            dynamic_cast<const sc_map_square_key*>(&other_key);

    bool equal = true;

    equal &= this->Y == other_key_square->Y;
    equal &= this->X == other_key_square->X;

    return equal;
}

//******************************************************************************
bool sc_map_square_key::operator<(const sc_map_key& other_key) const
{
    const sc_map_square_key* other_key_square =
            dynamic_cast<const sc_map_square_key*>(&other_key);

    bool smaller = false;

    if (this->Y < other_key_square->Y)
    {
        smaller = true;
    }
    else if (this->Y == other_key_square->Y)
    {
        if (this->X < other_key_square->X)
        {
            smaller = true;
        }
    }

    return smaller;
}
