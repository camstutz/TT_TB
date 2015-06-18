/*!
 * @file sc_map_range.hpp
 * @author Christian Amstutz
 * @date June 9, 2015
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
#include <vector>
#include <functional>
#include <ostream>

//******************************************************************************
template <typename key_T>
class sc_map_range
{
public:
    typedef key_T key_type;
    typedef std::vector<key_type> key_vector_type;

    enum direction{UP, DOWN};

    virtual ~sc_map_range() {};

    virtual sc_map_range* clone() const =0;

    virtual key_type first() const =0;
    virtual key_type last() const =0;

    virtual bool key_in_range(const key_type& key) const;
    virtual bool next_key(key_type& key) const =0;
    virtual key_vector_type get_key_vector() const;
};

//******************************************************************************

//******************************************************************************
template <typename key_T>
bool sc_map_range<key_T>::key_in_range(const key_type& key) const
{
    key_type range_key = first();
    do
    {
        if (range_key == key)
        {
            return true;
        }
    } while (next_key(range_key));

    return false;
}

//******************************************************************************
template <typename key_T>
typename sc_map_range<key_T>::key_vector_type
        sc_map_range<key_T>::get_key_vector() const
{
    key_vector_type key_vector;

    key_type key = first();
    do
    {
        key_vector.push_back(key);
    } while (next_key(key));

    return key_vector;
}
