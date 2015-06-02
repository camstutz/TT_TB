/*!
 * @file sc_map_list_key_range.hpp
 * @author Christian Amstutz
 * @date June 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_key_range.hpp"

#include <vector>

//******************************************************************************
template <typename key_T>
class sc_map_list_key_range : public sc_map_key_range<key_T>
{
public:
    typedef typename sc_map_key_range<key_T>::key_type key_type;

    sc_map_list_key_range();
    sc_map_list_key_range(const std::vector<key_type> keys);
    virtual ~sc_map_list_key_range() {};

    virtual sc_map_list_key_range* clone();

    void add_key(const key_type& new_key);
    //void add_key(const std::vector<key_type>& new_keys);

    virtual key_type first() const;
    virtual key_type last() const;
    virtual bool next_key(key_type& key) const;
    virtual bool key_in_range(const key_type& key) const;

    std::vector<key_type> get_key_vector() const;

private:
    std::vector<key_type> keys;
};

//******************************************************************************

//******************************************************************************
template <typename key_T>
sc_map_list_key_range<key_T>::sc_map_list_key_range()
{}

//******************************************************************************
template <typename key_T>
sc_map_list_key_range<key_T>::sc_map_list_key_range(
        const std::vector<key_type> keys) :
        keys(keys)
{}

//******************************************************************************
template <typename key_T>
typename sc_map_list_key_range<key_T>::sc_map_list_key_range*
        sc_map_list_key_range<key_T>::clone()
{
  return new sc_map_list_key_range<key_type>(*this);
}

//******************************************************************************
template <typename key_T>
void sc_map_list_key_range<key_T>::add_key(const key_type& new_key)
{
    keys.push_back(new_key);

    return;
}

////******************************************************************************
//template <typename key_T>
//void sc_map_list_key_range<key_T>::add_key(const std::vector<key_type>& new_keys)
//{
//    keys.insert(keys.end(), new_keys.begin(), new_keys.end());
//
//    return;
//}

//******************************************************************************
template <typename key_T>
typename sc_map_list_key_range<key_T>::key_type
        sc_map_list_key_range<key_T>::first() const
{
    return keys[0];
}

//******************************************************************************
template <typename key_T>
typename sc_map_list_key_range<key_T>::key_type
        sc_map_list_key_range<key_T>::last() const
{
    return keys[keys.size()-1];
}

//******************************************************************************
template <typename key_T>
bool sc_map_list_key_range<key_T>::next_key(key_type& key) const
{
    for (typename std::vector<key_type>::const_iterator key_it = keys.begin();
         key_it != keys.end();
         ++key_it)
    {
        if (*key_it == key)
        {
            ++key_it;
            if (key_it != keys.end())
            {
                key = *key_it;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

//******************************************************************************
template <typename key_T>
bool sc_map_list_key_range<key_T>::key_in_range(const key_type& key) const
{
    for (typename std::vector<key_type>::const_iterator key_it = keys.begin();
         key_it != keys.end();
         ++key_it)
    {
        if (*key_it == key)
        {
            return true;
        }
    }

    return false;
}

//******************************************************************************
template <typename key_T>
std::vector<typename sc_map_list_key_range<key_T>::key_type>
        sc_map_list_key_range<key_T>::get_key_vector() const
{
    return keys;
}
