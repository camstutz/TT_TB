/*!
 * @file sc_map_base.cpp
 * @author Christian Amstutz
 * @date Feb 19, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"

//******************************************************************************
template<typename object_type>
sc_map_base<object_type>::sc_map_base(const sc_module_name name)
        : objects(name)
{}

//******************************************************************************
template<typename object_type>
sc_vector_base::size_type sc_map_base<object_type>::size()
{
    return (objects.size());
}

//******************************************************************************
template<typename object_type>
typename sc_map_base<object_type>::iterator sc_map_base<object_type>::begin()
{
    return (iterator(*this, 0));
}

//******************************************************************************
template<typename object_type>
typename sc_map_base<object_type>::iterator sc_map_base<object_type>::end()
{
    return (iterator(*this, objects.size()));
}

//******************************************************************************
template<typename object_type>
void sc_map_base<object_type>::make_sensitive(
        sc_sensitive& sensitive_list) const
{
    // todo: change it to a traditional way of sensitivity lists
    // todo: make it possible to react on other than pos
    // todo: make it not to use the reference, but const
    for (auto& sens_object : objects) {
        sensitive_list << sens_object.pos();
    }

    return;
}

//******************************************************************************
template<typename trace_obj_type>
void sc_trace(sc_trace_file* tf, sc_map_base<trace_obj_type>& sc_map, const std::string& name)
{
    for (auto &my_object : sc_map) {
        std::ostringstream full_name;
        full_name << name << "." << my_object.name();
        sc_trace(tf, my_object, full_name.str().c_str());
    }
}

//******************************************************************************
template<typename object_type>
sc_map_iter<object_type>::sc_map_iter(sc_map_base<object_type>& sc_map, unsigned int pos) :
        sc_map(sc_map), pos(pos)
{}

//******************************************************************************
template<typename object_type>
bool sc_map_iter<object_type>::operator==(const sc_map_iter& other)
{
    return (pos == other.pos);
}

//******************************************************************************
template<typename object_type>
bool sc_map_iter<object_type>::operator!=(const sc_map_iter& other)
{
    return (pos != other.pos);
}

//******************************************************************************
template<typename object_type>
const sc_map_iter<object_type>& sc_map_iter<object_type>::operator++ ()
{
    ++pos; return (*this);
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_iter<object_type>::operator*()
{
    return (sc_map.objects[pos]);
}
