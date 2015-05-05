/*!
 * @file sc_map_linear.hpp
 * @author Christian Amstutz
 * @date May 4, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include "sc_map_iter_linear.hpp"

#include <systemc.h>

#include <string>
#include <sstream>
#include <map>
#include <utility>

//******************************************************************************
template <typename object_type>
class sc_map_linear : public sc_map_base<object_type>
{
    friend class sc_map_iter_linear<object_type>;

public:
    typedef sc_map_base<object_type> base;
    typedef sc_map_iter_linear<object_type> linear_iterator;
    typedef typename base::key_type key_type;
    typedef struct
    {
        key_type X_dim;
    } full_key_type;
    typedef typename base::size_type size_type;
    typedef typename std::map<key_type, size_type> map_type;

    static const key_type default_start_id;

    using base::bind;
    using base::operator();

    sc_map_linear(const size_type element_cnt_X, const sc_module_name name = "", const key_type start_id_X = default_start_id);
    virtual ~sc_map_linear() {};

    size_type size_X() const;

    //* todo: const version needed?
    object_type& at(const key_type key_X);
    object_type& operator[] (const key_type key_X);
    linear_iterator operator()(const key_type X_start, const key_type X_stop);

    std::pair<bool, full_key_type> get_key(object_type& object) const;
    virtual std::string key_string(object_type& map_element) const;

private:
    key_type start_id_X;

    map_type objects_map;

    size_type get_vect_pos(key_type pos_X);

    class creator
    {
    public:
        creator() {};
        object_type* operator() (const sc_module_name name,
                sc_map_linear<object_type>::key_type id);
    };
};

//******************************************************************************

//******************************************************************************

template <typename object_type>
const typename sc_map_linear<object_type>::key_type
        sc_map_linear<object_type>::default_start_id = 0;

//******************************************************************************

template <typename object_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_cnt_X,
        const sc_module_name name, const key_type start_id_X) :
        sc_map_base<object_type>(name)
{
    this->start_id_X = start_id_X;
    this->init(element_cnt_X, creator());

    for (size_type x = 0; x<element_cnt_X; ++x)
    {
        size_type vector_id = x;
        objects_map[start_id_X+x] = vector_id;
    }

    return;
}

//******************************************************************************
template <typename object_type>
typename sc_map_linear<object_type>::size_type sc_map_linear<object_type>::size_X() const
{
    return objects_map.size();
}

//******************************************************************************
template <typename object_type>
object_type& sc_map_linear<object_type>::at(const key_type key_X)
{
    // todo: at exception handling for out range accesses
    object_type& ret_object = *(this->objects[key_X]);

    return ret_object;
}

//******************************************************************************
template <typename object_type>
object_type& sc_map_linear<object_type>::operator[] (const key_type key_X)
{
    return at(key_X);
}

//******************************************************************************
template <typename object_type>
typename sc_map_linear<object_type>::linear_iterator
        sc_map_linear<object_type>::operator()(const key_type X_start,
        const key_type X_stop)
{
    sc_map_iter_linear<object_type> it(*this, X_start, X_stop);

    return it;
}

//******************************************************************************
template <typename object_type>
std::pair<bool, typename sc_map_linear<object_type>::full_key_type>
        sc_map_linear<object_type>::get_key(object_type& object) const
{
    std::pair<bool, full_key_type> full_key;
    full_key.first = false;

    typename map_type::const_iterator object_it = objects_map.begin();
    for (; object_it != objects_map.end(); ++object_it)
    {
        const object_type* map_object = this->objects[object_it->second];
        if (map_object == &object)
        {
            full_key.first = true;
            full_key.second.X_dim = object_it->first;
            break;
        }
    }

    return full_key;
}

//******************************************************************************
template <typename object_type>
std::string sc_map_linear<object_type>::key_string(object_type& map_element) const
{
    std::stringstream key_sstream;

    std::pair<bool, full_key_type> key_return = get_key(map_element);
    if (key_return.first)
    {
        full_key_type key = key_return.second;
        key_sstream << key.X_dim;
    }

    return key_sstream.str();
}

//******************************************************************************
template <typename object_type>
typename sc_map_linear<object_type>::size_type
        sc_map_linear<object_type>::get_vect_pos(key_type pos_X)
{
    size_type vector_pos = objects_map.at(pos_X);

    return vector_pos;
}

//******************************************************************************
template <typename object_type>
object_type* sc_map_linear<object_type>::creator::operator() (
        const sc_module_name name, sc_map_linear<object_type>::key_type id)
{
    std::stringstream full_name;
    
    full_name << name << sc_map_linear<object_type>::key_separator << id;

    return (new object_type(full_name.str().c_str()) );
}
