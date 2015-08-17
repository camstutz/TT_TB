/*!
 * @file sc_map_regular_range.hpp
 * @author Christian Amstutz
 * @date June 15, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include "sc_map_range.hpp"

//******************************************************************************
template <typename key_T>
class sc_map_regular_range : public sc_map_range<key_T>
{
public:
    typedef key_T key_type;

    sc_map_regular_range(const key_type& start_key, const key_type& end_key);
    virtual ~sc_map_regular_range() {};

    virtual sc_map_range<key_type>* clone() const =0;

    virtual key_type first() const;
    virtual key_type last() const;

    virtual bool next_key(key_type& key) const =0;

public:
    key_type start_key;
    key_type end_key;
};

//******************************************************************************

//******************************************************************************
template <typename key_T>
sc_map_regular_range<key_T>::sc_map_regular_range(const key_type& start_key,
        const key_type& end_key) :
        start_key(start_key),
        end_key(end_key)
{}

//******************************************************************************
template <typename key_T>
typename sc_map_regular_range<key_T>::key_type
        sc_map_regular_range<key_T>::first() const
{
    return start_key;
}

//******************************************************************************
template <typename key_T>
typename sc_map_regular_range<key_T>::key_type
        sc_map_regular_range<key_T>::last() const
{
    return end_key;
}
