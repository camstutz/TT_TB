/*!
 * @file sc_map_4d.hpp
 * @author Christian Amstutz
 * @date June 18, 2015
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

#include "sc_map_4d_key.hpp"
#include "sc_map_4d_range.hpp"

//******************************************************************************

template <typename object_T>
class sc_map_4d : public sc_map_base<sc_map_4d_range, object_T>
{
public:
    typedef sc_map_base<sc_map_4d_range, object_T> base;
    typedef typename base::range_type range_type;
    typedef typename base::key_type key_type;
    typedef typename base::key_vector_type key_vector_type;
    typedef typename base::key_type::index_type index_type;
    typedef typename base::size_type size_type;

    sc_map_4d(const size_type element_cnt_Z, const size_type element_cnt_Y, const size_type element_cnt_X, const size_type element_cnt_W, const sc_module_name name);
    sc_map_4d(const size_type element_cnt_Z, const size_type element_cnt_Y, const size_type element_cnt_X, const size_type element_cnt_W, const sc_module_name name, const index_type start_id_Z, const index_type start_id_Y, const index_type start_id_X, const index_type start_id_W);
    template <typename config_type>
    sc_map_4d(const size_type element_cnt_Z, const size_type element_cnt_Y, const size_type element_cnt_X, const size_type element_cnt_W, const sc_module_name name, const config_type configuration);
    template <typename config_type>
    sc_map_4d(const size_type element_cnt_Z, const size_type element_cnt_Y, const size_type element_cnt_X, const size_type element_cnt_W, const sc_module_name name, const config_type configuration, const index_type start_id_Z, const index_type start_id_Y, const index_type start_id_X, const index_type start_id_W);

    sc_map_4d(const key_type& start_key, const key_type& end_key, const sc_module_name name);
    template <typename config_type>
    sc_map_4d(const key_type& start_key, const key_type& end_key, const sc_module_name name, const config_type& configuration);

    sc_map_4d(const range_type& new_range, const sc_module_name name);
    template <typename config_type>
    sc_map_4d(const range_type& new_range, const sc_module_name name, const config_type& configuration);

    virtual ~sc_map_4d() {};

    object_T& at(const index_type& Z, const index_type& Y, const index_type& X, const index_type& W);

    const char* kind() const;
};

//******************************************************************************

//******************************************************************************
template <typename object_T>
sc_map_4d<object_T>::sc_map_4d(const size_type element_cnt_Z,
        const size_type element_cnt_Y, const size_type element_cnt_X,
        const size_type element_cnt_W, const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_4d_key(),
            sc_map_4d_key(element_cnt_Z-1, element_cnt_Y-1, element_cnt_X-1, element_cnt_W-1));

    this->init(range, typename base::creator());

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_4d<object_T>::sc_map_4d(const size_type element_cnt_Z,
        const size_type element_cnt_Y, const size_type element_cnt_X,
        const size_type element_cnt_W, const sc_module_name name,
        const index_type start_id_Z, const index_type start_id_Y,
        const index_type start_id_X, const index_type start_id_W) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_4d_key(start_id_Z, start_id_Y, start_id_X, start_id_W),
            sc_map_4d_key(start_id_Z+element_cnt_Z-1, start_id_Y+element_cnt_Y-1, start_id_X+element_cnt_X-1, start_id_W+element_cnt_W-1));

    this->init(range, typename base::creator());

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_4d<object_T>::sc_map_4d(const size_type element_cnt_Z,
        const size_type element_cnt_Y, const size_type element_cnt_X,
        const size_type element_cnt_W, const sc_module_name name,
        const config_type configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_4d_key(),
            sc_map_4d_key(element_cnt_Z-1, element_cnt_Y-1, element_cnt_X-1, element_cnt_W-1));

    this->init(range, typename base::creator(), configuration);

    //simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_4d<object_T>::sc_map_4d(const size_type element_cnt_Z,
        const size_type element_cnt_Y, const size_type element_cnt_X,
        const size_type element_cnt_W, const sc_module_name name,
        const config_type configuration, const index_type start_id_Z,
        const index_type start_id_Y, const index_type start_id_X,
        const index_type start_id_W) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(sc_map_4d_key(start_id_Z, start_id_Y, start_id_X, start_id_W),
            sc_map_4d_key(start_id_Z+element_cnt_Z-1, start_id_Y+element_cnt_Y-1, start_id_X+element_cnt_X-1, start_id_W+element_cnt_W-1));

    this->init(range, typename base::creator(), configuration);

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_4d<object_T>::sc_map_4d(const key_type& start_key,
        const key_type& end_key, const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator());

   // simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_4d<object_T>::sc_map_4d(const key_type& start_key,
        const key_type& end_key, const sc_module_name name,
        const config_type& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range = range_type(start_key, end_key);
    this->init(range, typename base::creator(), configuration);

  //  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
sc_map_4d<object_T>::sc_map_4d(const range_type& new_range,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator());

  //  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
template <typename config_type>
sc_map_4d<object_T>::sc_map_4d(const range_type& new_range,
        const sc_module_name name, const config_type& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator(), configuration);

  //  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename object_T>
object_T& sc_map_4d<object_T>::at(const index_type& Z, const index_type& Y,
        const index_type& X, const index_type& W)
{
    return base::at(key_type(Z, Y, X, W));
}

//******************************************************************************
template <typename object_T>
const char* sc_map_4d<object_T>::kind() const
{
    return ("sc_map_4d");
}
