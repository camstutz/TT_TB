/*!
 * @file sc_map_list.hpp
 * @author Christian Amstutz
 * @date June 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include <systemc.h>

#include <string>
#include <sstream>
#include "sc_map_list_range.hpp"

//******************************************************************************
template <typename key_value_T, typename object_T>
class sc_map_list : public sc_map_base<sc_map_list_range<key_value_T>, object_T>
{
public:
    typedef sc_map_base<sc_map_list_range<key_value_T>, object_T> base;
    typedef key_value_T key_value_type;
    typedef std::vector<key_value_type> key_value_vector_type;
    typedef typename base::range_type range_type;
    typedef typename base::key_type key_type;
    typedef typename base::key_vector_type key_vector_type;

    sc_map_list(const key_value_vector_type& key_vector, const sc_module_name name);
    template <typename config_T>
    sc_map_list(const key_value_vector_type& key_vector, const sc_module_name name, const config_T& configuration);
    sc_map_list(const range_type& new_range, const sc_module_name name);
    template <typename config_T>
    sc_map_list(const range_type& new_range, const sc_module_name name, const config_T& configuration);
    virtual ~sc_map_list() {};
};

//******************************************************************************

//******************************************************************************
template <typename value_T, typename object_T>
sc_map_list<value_T, object_T>::sc_map_list(const key_value_vector_type& key_vector,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range;

    for (typename key_value_vector_type::const_iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        range.add_key(key_type(*value_it));
    }

    this->init(range, typename base::creator());

    return;
}

//******************************************************************************
template <typename value_T, typename object_T>
template <typename config_T>
sc_map_list<value_T, object_T>::sc_map_list(const key_value_vector_type& key_vector,
        const sc_module_name name, const config_T& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range;

    for (typename key_value_vector_type::const_iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        range.add_key(key_type(*value_it));
    }

    this->init(range, typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename value_T, typename object_T>
sc_map_list<value_T, object_T>::sc_map_list(const range_type& new_range,
        const sc_module_name name)
{
    this->init(new_range, typename base::creator());

    return;
}

//******************************************************************************
template <typename value_T, typename object_T>
template <typename config_T>
sc_map_list<value_T, object_T>::sc_map_list(const range_type& new_range,
        const sc_module_name name, const config_T& configuration)
{
    this->init(new_range, typename base::creator(), configuration);

    return;
}
