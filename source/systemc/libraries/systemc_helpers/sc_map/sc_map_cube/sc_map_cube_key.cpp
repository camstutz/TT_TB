/*!
 * @file sc_map_cube_key.cpp
 * @author Christian Amstutz
 * @date June 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_cube_key.hpp"

//******************************************************************************
sc_map_cube_key::sc_map_cube_key() :
        Z(sc_map_regular_key::default_start_id),
        Y(sc_map_regular_key::default_start_id),
        X(sc_map_regular_key::default_start_id)
{}

//******************************************************************************
sc_map_cube_key::sc_map_cube_key(const index_type& Z, const index_type& Y,
        const index_type& X) :
        Z(Z),
        Y(Y),
        X(X)
{}

//******************************************************************************
std::string sc_map_cube_key::get_string() const
{
    std::stringstream collection_stream;
    collection_stream << Z;
    collection_stream << sc_map::key_sub_separator_char;
    collection_stream << Y;
    collection_stream << sc_map::key_sub_separator_char;
    collection_stream << X;

    return collection_stream.str();
}

//******************************************************************************
bool sc_map_cube_key::operator==(const sc_map_key& other_key) const
{
    const sc_map_cube_key* other_key_cube =
            dynamic_cast<const sc_map_cube_key*>(&other_key);

    bool equal = true;

    equal &= this->Z == other_key_cube->Z;
    equal &= this->Y == other_key_cube->Y;
    equal &= this->X == other_key_cube->X;

    return equal;
}

//******************************************************************************
bool sc_map_cube_key::operator<(const sc_map_key& other_key) const
{
    const sc_map_cube_key* other_key_cube =
            dynamic_cast<const sc_map_cube_key*>(&other_key);

    bool smaller = false;

    if (this->Z < other_key_cube->Z)
    {
        smaller = true;
    }
    else if (this->Z == other_key_cube->Z)
    {
        if (this->Y < other_key_cube->Y)
        {
            smaller = true;
        }
        else if (this->Y == other_key_cube->Y)
        {
            if (this->X < other_key_cube->X)
            {
                smaller = true;
            }
        }
    }

    return smaller;
}
