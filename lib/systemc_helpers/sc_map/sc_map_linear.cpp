/*!
 * @file sc_map_linear.cpp
 * @author Christian Amstutz
 * @date Feb 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_map_linear.hpp"

//******************************************************************************
template<typename object_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_count,
        const sc_module_name name, const key_type start_id) :
        sc_map_base<object_type>(name) {

    this->start_id = start_id;
    this->objects.init(element_count, creator());

    for (size_type i = 0; i<element_count; ++i) {
        objects_map[start_id+i] = &this->objects[i];
    }

    return;
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_linear<object_type>::at(const key_type key)
{
    return (*objects_map[key]);
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_linear<object_type>::operator[] (const key_type key)
{
    return (at(key));
}

//******************************************************************************
template<typename object_type>
template<typename signal_type>
bool sc_map_linear<object_type>::bind(sc_map_linear<signal_type>& signals_map)
{
    if (this->size() !=  signals_map.size())
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
object_type* sc_map_linear<object_type>::creator::operator() (
        const sc_module_name name, sc_map_linear<object_type>::key_type id)
{
    std::string full_name(name);
    std::size_t id_pos = full_name.find_first_of('_');
    full_name = full_name.substr(0, id_pos);
    full_name = full_name + "_" + std::to_string(id);

    return (new object_type(full_name.c_str()) );
}
