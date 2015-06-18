/*!
 * @file sc_map_linear_key.cpp
 * @author Christian Amstutz
 * @date May 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sc_map_linear_key.hpp"

//******************************************************************************
sc_map_linear_key::sc_map_linear_key(index_type X) :
        X(X)
{}

//******************************************************************************
std::string sc_map_linear_key::get_string() const
{
    std::stringstream collection_stream;
    collection_stream << X;

    return collection_stream.str();
}

//******************************************************************************
bool sc_map_linear_key::operator==(const sc_map_key& other_key) const
{
    const sc_map_linear_key* other_key_linear =
            dynamic_cast<const sc_map_linear_key*>(&other_key);

    return (this->X == other_key_linear->X);
}

//******************************************************************************
bool sc_map_linear_key::operator<(const sc_map_key& other_key) const
{
    const sc_map_linear_key* other_key_linear =
            dynamic_cast<const sc_map_linear_key*>(&other_key);

    return (this->X < other_key_linear->X);
}
