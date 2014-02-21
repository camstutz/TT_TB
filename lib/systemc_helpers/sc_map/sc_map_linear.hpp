/*!
 * @file sc_map_linear.hpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <map>
#include <utility>

#include <systemc.h>

#include "sc_map_base.hpp"

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
    std::map<key_type, object_type*> objects_map;

    class creator
    {
    public:
        creator() {};
        object_type* operator() (const sc_module_name name, sc_map_linear<object_type>::key_type id);
    };
};

#include "sc_map_linear.cpp"
