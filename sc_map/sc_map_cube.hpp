/*!
 * @file sc_map_cube.hpp
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
#include "sc_map_iter_cube.hpp"

#include <systemc.h>

#include <string>
#include <sstream>
#include <map>
#include <utility>

//******************************************************************************
template <typename object_type>
class sc_map_cube : public sc_map_base<object_type>
{
    friend class sc_map_iter_cube<object_type>;

public:
    typedef sc_map_base<object_type> base;
    typedef sc_map_iter_cube<object_type> cube_iterator;
    typedef typename base::key_type key_type;
    typedef struct
    {
        key_type Z_dim;
        key_type Y_dim;
        key_type X_dim;
    } full_key_type;
    typedef typename base::size_type size_type;
    typedef std::map<key_type, size_type> map_1d_type;
    typedef std::map<key_type, map_1d_type> map_2d_type;
    typedef std::map<key_type, map_2d_type> map_type;

    static const key_type default_start_id_Z;
    static const key_type default_start_id_Y;
    static const key_type default_start_id_X;

    using base::bind;
    using base::operator();

    sc_map_cube(const size_type element_cnt_Z, const size_type element_cnt_Y,
            const size_type element_cnt_X, const sc_module_name name = "",
            const key_type start_id_Z = default_start_id_Z,
            const key_type start_id_Y = default_start_id_Y,
            const key_type start_id_X = default_start_id_X);
    virtual ~sc_map_cube() {};

    size_type size_Z();
    size_type size_Y();
    size_type size_X();

    object_type& at(const key_type key_Z, const key_type key_Y, const key_type key_X);
    cube_iterator operator()(const key_type Z_start, const key_type Z_stop,
                             const key_type Y_start, const key_type Y_stop,
                             const key_type X_start, const key_type X_stop);

    std::pair<bool, full_key_type> get_key(object_type& object) const;
    virtual std::string key_string(object_type& map_element) const;

private:
    const key_type start_id_Z;
    const key_type start_id_Y;
    const key_type start_id_X;

    map_type objects_map;

    size_type get_vect_pos(key_type pos_Z, key_type pos_Y, key_type pos_X);

    class creator
    {
    public:
        size_type size_Z;
        size_type size_Y;
        size_type size_X;

        creator(const size_type size_Z, const size_type size_Y,
                const size_type size_X);
        object_type* operator() (const sc_module_name name, size_type id);
    };
};

//******************************************************************************

//******************************************************************************

template<typename object_type>
const typename sc_map_cube<object_type>::key_type
        sc_map_cube<object_type>::default_start_id_Z = 0;

template<typename object_type>
const typename sc_map_cube<object_type>::key_type
        sc_map_cube<object_type>::default_start_id_Y = 0;

template<typename object_type>
const typename sc_map_cube<object_type>::key_type
        sc_map_cube<object_type>::default_start_id_X = 0;

//******************************************************************************

template<typename object_type>
sc_map_cube<object_type>::sc_map_cube(
        const size_type element_cnt_Z, const size_type element_cnt_Y, const size_type element_cnt_X,
        const sc_module_name name, const key_type start_id_Z, const key_type start_id_Y,
        const key_type start_id_X) : sc_map_base<object_type>(name),
        start_id_Z(start_id_Z), start_id_Y(start_id_Y), start_id_X(start_id_X)
{
    size_type element_cnt = element_cnt_X * element_cnt_Y * element_cnt_Z;
    this->init(element_cnt, creator(element_cnt_Z, element_cnt_Y, element_cnt_X));

    for (size_type z = 0; z<element_cnt_Z; ++z) {
        for (size_type y = 0; y<element_cnt_Y; ++y) {
            for (size_type x = 0; x<element_cnt_X; ++x) {
                key_type vector_id = z*element_cnt_Y*element_cnt_X + y*element_cnt_X + x;
                objects_map[start_id_Z+z][start_id_Y+y][start_id_X+x] = vector_id;
            }
        }
    }

    return;
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::size_Z()
{
    return objects_map.size();
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::size_Y()
{
    typename map_type::iterator first_Z = objects_map.begin();
    return first_Z->second.size();
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::size_X()
{
    typename map_type::iterator first_Z = objects_map.begin();
    typename map_2d_type::iterator first_Y = first_Z->second.begin();
    return first_Y->second.size();
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_cube<object_type>::at(const key_type key_Z,
        const key_type key_Y, const key_type key_X)
{
    object_type& ret_object = *this->objects[get_vect_pos(key_Z, key_Y, key_X)];
    return  ret_object;
}

//******************************************************************************
template <typename object_type>
typename sc_map_cube<object_type>::cube_iterator sc_map_cube<object_type>::operator()(
                         const key_type Z_start, const key_type Z_stop,
                         const key_type Y_start, const key_type Y_stop,
                         const key_type X_start, const key_type X_stop)
{
    sc_map_iter_cube<object_type> it(*this, Z_start, Z_stop, Y_start, Y_stop,
            X_start, X_stop);

    return it;
}

//******************************************************************************
template<typename object_type>
std::pair<bool, typename sc_map_cube<object_type>::full_key_type>
        sc_map_cube<object_type>::get_key(object_type& object) const
{
    std::pair<bool, full_key_type> full_key;
    full_key.first = false;

    typename map_type::const_iterator square_part_it = objects_map.begin();
    for (; square_part_it != objects_map.end(); ++square_part_it)
    {
        typename map_2d_type::const_iterator linear_part_it;
        linear_part_it = square_part_it->second.begin();
        for (; linear_part_it != square_part_it->second.end(); ++linear_part_it)
        {
            typename map_1d_type::const_iterator element_it;
            element_it = linear_part_it->second.begin();
            for (; element_it != linear_part_it->second.end(); ++element_it)
            {
                const object_type* map_object;
                map_object = this->objects[element_it->second];
                if (map_object == &object)
                {
                    full_key.first = true;
                    full_key.second.Z_dim = square_part_it->first;
                    full_key.second.Y_dim = linear_part_it->first;
                    full_key.second.X_dim = element_it->first;
                    break;
                }
            }
        }
    }

    return full_key;
}

//******************************************************************************
template<typename object_type>
std::string sc_map_cube<object_type>::key_string(object_type& map_element) const
{
    std::stringstream key_sstream;

    std::pair<bool, full_key_type> key_return = get_key(map_element);
    if (key_return.first)
    {
        full_key_type key = key_return.second;
        key_sstream << key.Z_dim << sc_map_base<object_type>::key_sub_separator
                    << key.Y_dim << sc_map_base<object_type>::key_sub_separator
                    << key.X_dim;
    }

    return key_sstream.str();
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::get_vect_pos(key_type pos_Z, key_type pos_Y,
        key_type pos_X)
{
    // todo: at exception handling for out of range accesses
    size_type vector_pos = objects_map.at(pos_Z).at(pos_Y).at(pos_X);

    return vector_pos;
}

//******************************************************************************
template<typename object_type>
sc_map_cube<object_type>::creator::creator(
        const sc_map_cube<object_type>::size_type size_Z,
        const sc_map_cube<object_type>::size_type size_Y,
        const sc_map_cube<object_type>::size_type size_X) :
        size_Z(size_Z), size_Y(size_Y), size_X(size_X)
{}

//******************************************************************************
template<typename object_type>
object_type* sc_map_cube<object_type>::creator::operator() (
        const sc_module_name name, sc_map_cube<object_type>::size_type id)
{
    // todo: integrate a label for the dimensions

    sc_map_cube<object_type>::key_type id_Z = id / (size_X*size_Y);
    sc_map_cube<object_type>::key_type id_Y = (id / size_X) % size_Y;
    sc_map_cube<object_type>::key_type id_X = id % size_X;

    std::stringstream full_name;
    full_name << name;

    full_name << sc_map_cube<object_type>::key_separator
              << id_Z << sc_map_cube<object_type>::key_sub_separator
              << id_Y << sc_map_cube<object_type>::key_sub_separator
              << id_X;

    return (new object_type(full_name.str().c_str()));
}
