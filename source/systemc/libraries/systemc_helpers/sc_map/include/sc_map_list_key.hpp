/*!
 * @file sc_map_list_key.hpp
 * @author Christian Amstutz
 * @date August 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_key.hpp"

#include <string>
#include <sstream>

//******************************************************************************
template <typename value_T>
class sc_map_list_key : public sc_map_key
{
public:
    typedef value_T value_type;

    value_type value;

    sc_map_list_key();
    sc_map_list_key(value_type value);
    virtual ~sc_map_list_key() {};

    virtual std::string get_string() const;

    virtual bool operator==(const sc_map_key& other_key) const;
    virtual bool operator<(const sc_map_key& other_key) const;
};

//*****************************************************************************

//******************************************************************************
template <typename value_T>
sc_map_list_key<value_T>::sc_map_list_key()
{}

//******************************************************************************
template <typename value_T>
sc_map_list_key<value_T>::sc_map_list_key(value_type value) :
        value(value)
{}

//******************************************************************************
template <typename value_T>
std::string sc_map_list_key<value_T>::get_string() const
{
    std::stringstream collection_stream;
    collection_stream << value;

    return collection_stream.str();
}

//******************************************************************************
template <typename value_T>
bool sc_map_list_key<value_T>::operator==(const sc_map_key& other_key) const
{
    const sc_map_list_key* other_key_linear =
            dynamic_cast<const sc_map_list_key<value_type>*>(&other_key);

    return (this->value == other_key_linear->value);
}

//******************************************************************************
template <typename value_T>
bool sc_map_list_key<value_T>::operator<(const sc_map_key& other_key) const
{
    const sc_map_list_key* other_key_linear =
            dynamic_cast<const sc_map_list_key<value_type>*>(&other_key);

    return (this->value < other_key_linear->value);
}
