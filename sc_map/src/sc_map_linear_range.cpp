/*!
 * @file sc_map_linear_range.cpp
 * @author Christian Amstutz
 * @date June 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "../include/sc_map_linear_range.hpp"

//******************************************************************************
sc_map_linear_range::sc_map_linear_range() :
        sc_map_regular_range(sc_map_linear_key(0), sc_map_linear_key(0)),
        X_dir(UP)
{}
    // todo:: this is basically not correct!

//******************************************************************************
sc_map_linear_range::sc_map_linear_range(const key_type& start_key,
        const key_type& end_key) :
        sc_map_regular_range(start_key, end_key)
{
    init(NULL, start_key, end_key);

    return;
}

//******************************************************************************
sc_map_linear_range::sc_map_linear_range(
        const sc_map_range<key_type>* base_range,
        const key_type& start_key, const key_type& end_key) :
        sc_map_regular_range(start_key, end_key)
{
    init(base_range, start_key, end_key);

    return;
}

//******************************************************************************
void sc_map_linear_range::init(const sc_map_range<key_type>* base_range, const key_type& start_key, const key_type& end_key)
{
    if (start_key <= end_key)
    {
        X_dir = UP;
    }
    else
    {
        X_dir = DOWN;
    }

    return;
}

//******************************************************************************
sc_map_linear_range* sc_map_linear_range::clone() const
{
  return new sc_map_linear_range(*this);
}

//******************************************************************************
bool sc_map_linear_range::next_key(key_type& key) const
{
    sc_map_linear_key* key_linear = dynamic_cast<sc_map_linear_key*>(&key);
    sc_map_linear_key new_key;

    if (*key_linear == end_key)
    {
        return false;
    }

    if (X_dir == UP)
    {
        new_key.X = key_linear->X + 1;
    }
    else
    {
        new_key.X = key_linear->X - 1;
    }

    *key_linear = new_key;

    return true;
}
