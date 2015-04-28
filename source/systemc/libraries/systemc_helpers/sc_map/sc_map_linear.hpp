/*!
 * @file sc_map_linear.hpp
 * @author Christian Amstutz
 * @date December 10, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <map>
#include <utility>

#include <systemc.h>

#include "sc_map_base.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_linear : public sc_map_base<object_type>
{
public:
    typedef typename sc_map_base<object_type>::key_type key_type;
    typedef struct
    {
        key_type X_dim;
    } full_key_type;
    typedef typename sc_map_base<object_type>::size_type size_type;
    typedef typename std::map<key_type, object_type*> map_type;

    static const int default_start_id = 0;

    sc_map_linear(const size_type element_count, const sc_module_name name = "",
            const key_type start_id = default_start_id);

    //* todo: const version needed?
    object_type& at(const key_type key);
    object_type& operator[] (const key_type key);
    std::pair<bool, full_key_type> get_key(object_type& object) const;

    template<typename signal_type>
    bool bind(sc_map_linear<signal_type>& signals_map);

private:
    key_type start_id;
    map_type objects_map;

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
template<typename object_type>
sc_map_linear<object_type>::sc_map_linear(const size_type element_count,
        const sc_module_name name, const key_type start_id) :
        sc_map_base<object_type>(name) {

    this->start_id = start_id;
    this->init(element_count, creator());

    for (size_type i = 0; i<element_count; ++i) {
        objects_map[start_id+i] = this->objects[i];
    }

    return;
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_linear<object_type>::at(const key_type key)
{
    // todo: at exception handling for out range accesses
    return (*objects_map.at(key));
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_linear<object_type>::operator[] (const key_type key)
{
    return (at(key));
}

//******************************************************************************
template<typename object_type>
std::pair<bool, typename sc_map_linear<object_type>::full_key_type>
        sc_map_linear<object_type>::get_key(object_type& object) const
{
    std::pair<bool, full_key_type> full_key;
    full_key.first = false;

    typename map_type::const_iterator object_it = objects_map.begin();
    for (; object_it != objects_map.end(); ++object_it)
    {
        if (object_it->second == &object)
        {
            full_key.first = true;
            full_key.second.X_dim = object_it->first;
            break;
        }
    }

    return (full_key);
}

//******************************************************************************
template<typename object_type>
template<typename signal_type>
bool sc_map_linear<object_type>::bind(sc_map_linear<signal_type>& signals_map)
{
    if (sc_map_base<object_type>::size() !=  signals_map.size())
    {
        std::cerr << "Error: Binding of port ("
                << this->name()
                << ") with signal ("
                << signals_map.name()
                << ") of different dimension."
                << std::endl;
        return(false);
    }

    sc_map_base<object_type>::bind(signals_map);

    return (true);
}

//******************************************************************************
template<typename object_type>
object_type* sc_map_linear<object_type>::creator::operator() (
        const sc_module_name name, sc_map_linear<object_type>::key_type id)
{
    std::stringstream full_name;
    
    full_name << name << "-" << id;

    return (new object_type(full_name.str().c_str()) );
}
