/*!
 * @file sc_map_cube.cpp
 * @author Christian Amstutz
 * @date Mar 12, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_map_cube.hpp"

//******************************************************************************
template<typename object_type>
sc_map_cube<object_type>::sc_map_cube(
        const size_type element_cnt_Z, const size_type element_cnt_Y, const size_type element_cnt_X,
        const sc_module_name name, const key_type start_id_Z, const key_type start_id_Y,
        const key_type start_id_X) : sc_map_base<object_type>(name),
        start_id_Z(start_id_Z), start_id_Y(start_id_Y), start_id_X(start_id_X)
{
    size_type element_cnt = element_cnt_X * element_cnt_Y * element_cnt_Z;
    this->objects.init(element_cnt, creator(element_cnt_Z, element_cnt_Y, element_cnt_X));

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
    return (objects_map.size());
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::size_Y()
{
    auto first_Z = objects_map.begin();
    return (first_Z->second.size() );
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::size_X()
{
    auto first_Z = objects_map.begin();
    auto first_Y = first_Z->second.begin();
    return (first_Y->second.size() );
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_cube<object_type>::at(const key_type key_Z,
        const key_type key_Y, const key_type key_X)
{
    object_type& ret_object = this->objects[get_vect_pos(key_Z, key_Y, key_X)];
    return (ret_object);
}

//******************************************************************************
template<typename object_type>
std::pair<bool, typename sc_map_cube<object_type>::full_key_type>
        sc_map_cube<object_type>::get_key(object_type& object) const
{
    std::pair<bool, full_key_type> full_key;
    full_key.first = false;

    for (auto Z_dim_element : objects_map)
    {
        for (auto Y_dim_element : Z_dim_element.second)
        {
            for (auto map_element : Y_dim_element.second)
            {
                const object_type* map_object = &this->objects[map_element.second];
                if (map_object == &object)
                {
                    full_key.first = true;
                    full_key.second.Z_dim = Z_dim_element.first;
                    full_key.second.Y_dim = Y_dim_element.first;
                    full_key.second.X_dim = map_element.first;
                    break;
                }
            }
        }
    }

    return (full_key);
}

//******************************************************************************
template<typename object_type>
sc_map_iter_cube<object_type> sc_map_cube<object_type>::begin_partial(
        const key_type pos_Z, const bool iterate_Z,
        const key_type pos_Y, const bool iterate_Y,
        const key_type pos_X, const bool iterate_X)
{
    key_type start_Z, stop_Z, start_Y, stop_Y, start_X, stop_X;

    if (iterate_Z)
    {
        start_Z = start_id_Z;
        stop_Z = start_id_Z+size_Z()-1;
    }
    else
    {
        start_Z = pos_Z;
        stop_Z = pos_Z;
    }

    if (iterate_Y)
    {
        start_Y = start_id_Y;
        stop_Y = start_id_Y+size_Y()-1;
    }
    else
    {
        start_Y = pos_Y;
        stop_Y = pos_Y;
    }

    if (iterate_X)
    {
        start_X = start_id_X;
        stop_X = start_id_X+size_X()-1;
    }
    else
    {
        start_X = pos_X;
        stop_X = pos_X;
    }

    sc_map_iter_cube<object_type> cube_map_it(*this,
            start_Z, stop_Z, iterate_Z,
            start_Y, stop_Y, iterate_Y,
            start_X, stop_X, iterate_X);

    return (cube_map_it);
}

//******************************************************************************
template<typename object_type>
sc_map_iter_cube<object_type> sc_map_cube<object_type>::begin_partial(
        const key_type start_Z, const key_type stop_Z, const bool iterate_Z,
        const key_type start_Y, const key_type stop_Y, const bool iterate_Y,
        const key_type start_X, const key_type stop_X, const bool iterate_X)
{
    sc_map_iter_cube<object_type> cube_map_it(*this,
            start_Z, stop_Z, iterate_Z,
            start_Y, stop_Y, iterate_Y,
            start_X, stop_X, iterate_X);

    return (cube_map_it);
}

//******************************************************************************
template<typename object_type>
template<typename signal_type>
bool sc_map_cube<object_type>::bind(sc_map_cube<signal_type>& signals_map)
{
    if ( (this->size_Z() !=  signals_map.size_Z()) &
            (this->size_Y() !=  signals_map.size_Y()) &
            (this->size_X() !=  signals_map.size_X()) )
    {
        std::cout << "Error: Binding of port with signal of different dimension."
                << std::endl;
        return(false);
    }

    this->objects.bind(signals_map.objects);

    return (true);
}

//******************************************************************************
template<typename object_type>
typename sc_map_cube<object_type>::size_type
        sc_map_cube<object_type>::get_vect_pos(key_type pos_Z, key_type pos_Y,
        key_type pos_X)
{
    // todo: at exception handling for out of range accesses
    size_type vector_pos = objects_map.at(pos_Z).at(pos_Y).at(pos_X);

    return (vector_pos);
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

    // todo: only remove if there is number in the end of name
    std::string full_name(name);
    std::size_t id_pos = full_name.find_first_of('_');
    full_name = full_name.substr(0, id_pos);
    full_name = full_name + "_" + std::to_string(id_Z) + "-"
            + std::to_string(id_Y) + "-" + std::to_string(id_X);

    return (new object_type(full_name.c_str()));
}
