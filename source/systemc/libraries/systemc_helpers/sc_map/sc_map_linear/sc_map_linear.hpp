/*!
 * @file sc_map_linear.hpp
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

#include "../sc_map_base.hpp"
#include "sc_map_linear_key.hpp"
#include <systemc.h>

#include <string>
#include <sstream>
#include "sc_map_linear_range.hpp"

//******************************************************************************

template <typename object_T>
class sc_map_linear : public sc_map_base<sc_map_linear_range, object_T>
{
public:
    typedef sc_map_base<sc_map_linear_range, object_T> base;
    typedef typename base::range_type range_type;
    typedef typename base::key_type key_type;
    typedef typename base::key_vector_type key_vector_type;
    typedef typename base::key_type::index_type index_type;
    typedef typename base::size_type size_type;

    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const index_type start_id_X = sc_map_linear_key::default_start_id);
    template <typename config_type>
    sc_map_linear(const size_type element_cnt_X, const sc_module_name name, const config_type configuration, const index_type start_id_X = sc_map_linear_key::default_start_id);
    sc_map_linear(const key_type start_key, const key_type end_key, const sc_module_name name);
    template <typename config_type>
    sc_map_linear(const key_type start_key, const key_type end_key, const sc_module_name name, const config_type configuration);
    sc_map_linear(const range_type new_range, const sc_module_name name);
    template <typename config_type>
    sc_map_linear(const range_type new_range, const sc_module_name name, const config_type configuration);
    virtual ~sc_map_linear() {};
};

//******************************************************************************

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const index_type start_id_X) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_linear_key(start_id_X),
            sc_map_linear_key(start_id_X+element_cnt_X-1));

    this->init(range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const config_type configuration,
        const index_type start_id_X) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_linear_key(start_id_X),
                sc_map_linear_key(start_id_X+element_cnt_X-1));

    this->init(range, typename base::creator(), configuration);
//  sink_configurable::sink_configurable(const char*, const std::vector<sink_config>&)’

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const key_type start_key,
        const key_type end_key, const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const key_type start_key,
        const key_type end_key, const sc_module_name name,
        const config_type configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator(), configuration);

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_linear<object_T>::sc_map_linear(const range_type new_range,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_linear<object_T>::sc_map_linear(const range_type new_range,
        const sc_module_name name, const config_type configuration) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator(), configuration);

    return;
}
