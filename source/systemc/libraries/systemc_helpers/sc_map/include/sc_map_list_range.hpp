/*!
 * @file sc_map_list_range.hpp
 * @author Christian Amstutz
 * @date August 25, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_list_key.hpp"

#include "sc_map_range.hpp"

#include <vector>

//******************************************************************************
template <typename value_T>
class sc_map_list_range : public sc_map_range<sc_map_list_key<value_T> >
{
public:
    typedef sc_map_range<sc_map_list_key<value_T> > base;
    typedef value_T value_type;
    typedef sc_map_list_key<value_type> key_type;

    sc_map_list_range();
    sc_map_list_range(const std::vector<key_type>& keys);
    sc_map_list_range(const std::vector<value_type>& values);
    sc_map_list_range(const sc_map_range<key_type>* source_range, const key_type& start_key, const key_type& end_key);
    virtual ~sc_map_list_range() {};

    virtual sc_map_list_range<value_type>* clone() const;

    void add_key(const key_type& new_key);
    //void add_key(const std::vector<key_type>& new_keys);

    virtual key_type first() const;
    virtual key_type last() const;
    virtual bool next_key(key_type& key) const;

private:
    std::vector<key_type> keys;
};

//******************************************************************************

//******************************************************************************
template <typename value_T>
sc_map_list_range<value_T>::sc_map_list_range()
{}

//******************************************************************************
template <typename value_T>
sc_map_list_range<value_T>::sc_map_list_range(
        const std::vector<key_type>& keys) :
        keys(keys)
{}

//******************************************************************************
template <typename value_T>
sc_map_list_range<value_T>::sc_map_list_range(
        const std::vector<value_type>& values)
{
    for (typename std::vector<value_type>::const_iterator value_it = values.begin();
         value_it != values.end();
         ++ value_it)
    {
        key_type key = key_type(*value_it);
        keys.push_back(key);
    }

    return;
}

//******************************************************************************
template <typename value_T>
sc_map_list_range<value_T>::sc_map_list_range(
        const sc_map_range<key_type>* source_range, const key_type& start_key,
        const key_type& end_key)
{

    if (source_range->key_in_range(start_key))
    {
        key_type key = start_key;

        do
        {
            add_key(key);
        } while (source_range->next_key(key));
    }
    else
    {
        return;
    }

    return;
}

//******************************************************************************
template <typename value_T>
sc_map_list_range<value_T>* sc_map_list_range<value_T>::clone() const
{
    return new sc_map_list_range<value_type>(*this);
}

//******************************************************************************
template <typename value_T>
void sc_map_list_range<value_T>::add_key(const key_type& new_key)
{
    keys.push_back(new_key);

    return;
}

////******************************************************************************
//template <typename key_T>
//void sc_map_list_range<key_T>::add_key(const std::vector<key_type>& new_keys)
//{
//    keys.insert(keys.end(), new_keys.begin(), new_keys.end());
//
//    return;
//}

//******************************************************************************
template <typename key_T>
typename sc_map_list_range<key_T>::key_type
        sc_map_list_range<key_T>::first() const
{
    return keys[0];
}

//******************************************************************************
template <typename key_T>
typename sc_map_list_range<key_T>::key_type
        sc_map_list_range<key_T>::last() const
{
    return keys[keys.size()-1];
}

//******************************************************************************
template <typename key_T>
bool sc_map_list_range<key_T>::next_key(key_type& key) const
{
    // todo: reverse access

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
