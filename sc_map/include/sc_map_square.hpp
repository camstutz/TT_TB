/*!
 * @file sc_map_square.hpp
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
#include "sc_map_square_key.hpp"
#include "sc_map_square_range.hpp"

//******************************************************************************

template <typename object_T>
class sc_map_square : public sc_map_base<sc_map_square_range, object_T>
{
public:
    typedef sc_map_base<sc_map_square_range, object_T> base;
    typedef typename base::range_type range_type;
    typedef typename base::key_type key_type;
    typedef typename base::key_vector_type key_vector_type;
    typedef typename base::key_type::index_type index_type;
    typedef typename base::size_type size_type;

    sc_map_square(const size_type element_cnt_Y, const size_type element_cnt_X, const sc_module_name name);
    sc_map_square(const size_type element_cnt_Y, const size_type element_cnt_X, const sc_module_name name, const index_type start_id_Y, const index_type start_id_X);
    template <typename config_type>
    sc_map_square(const size_type element_cnt_Y, const size_type element_cnt_X, const sc_module_name name, const config_type configuration);
    template <typename config_type>
    sc_map_square(const size_type element_cnt_Y, const size_type element_cnt_X, const sc_module_name name, const config_type configuration, const index_type start_id_Y, const index_type start_id_X);

    sc_map_square(const key_type& start_key, const key_type& end_key, const sc_module_name name);
    template <typename config_type>
    sc_map_square(const key_type& start_key, const key_type& end_key, const sc_module_name name, const config_type& configuration);

    sc_map_square(const range_type& new_range, const sc_module_name name);
    template <typename config_type>
    sc_map_square(const range_type& new_range, const sc_module_name name, const config_type& configuration);

    virtual ~sc_map_square() {};

    object_T& at(const index_type& Y, const index_type& X);
};

//******************************************************************************

//******************************************************************************
template <typename object_T>
sc_map_square<object_T>::sc_map_square(const size_type element_cnt_Y,
        const size_type element_cnt_X, const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_square_key(),
            sc_map_square_key(element_cnt_Y-1, element_cnt_X-1));

    this->init(range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_square<object_T>::sc_map_square(const size_type element_cnt_Y,
        const size_type element_cnt_X, const sc_module_name name,
        const index_type start_id_Y, const index_type start_id_X) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_square_key(start_id_Y, start_id_X),
            sc_map_square_key(start_id_Y+element_cnt_Y-1, start_id_X+element_cnt_X-1));

    this->init(range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_square<object_T>::sc_map_square(const size_type element_cnt_Y,
        const size_type element_cnt_X, const sc_module_name name,
        const config_type configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_square_key(),
            sc_map_square_key(element_cnt_Y-1, element_cnt_X-1));

    this->init(range, typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_square<object_T>::sc_map_square(const size_type element_cnt_Y,
        const size_type element_cnt_X, const sc_module_name name,
        const config_type configuration, const index_type start_id_Y,
        const index_type start_id_X) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_square_key(start_id_Y, start_id_X),
            sc_map_square_key(start_id_Y+element_cnt_Y-1, start_id_X+element_cnt_X-1));

    this->init(range, typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_square<object_T>::sc_map_square(const key_type& start_key,
        const key_type& end_key, const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_square<object_T>::sc_map_square(const key_type& start_key,
        const key_type& end_key, const sc_module_name name,
        const config_type& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_square<object_T>::sc_map_square(const range_type& new_range,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_square<object_T>::sc_map_square(const range_type& new_range,
        const sc_module_name name, const config_type& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename object_T>
object_T& sc_map_square<object_T>::at(const index_type& Y,
        const index_type& X)
{
    return base::at(key_type(Y, X));
}
