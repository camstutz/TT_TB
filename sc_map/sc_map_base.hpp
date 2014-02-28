/*!
 * @file sc_map_base.hpp
 * @author Christian Amstutz
 * @date Feb 28, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <cstddef>
#include <string>

#include <systemc.h>

#include "sc_map_iter_sequential.hpp"

//* todo: should sc_map_base inherit from sc_object?
//* todo: otherwise add name data member

//******************************************************************************
template<typename object_type>
class sc_map_base
{
public:
    typedef int key_type;
    //* todo: are these typedefs necessary?
    typedef sc_map_iter_sequential<object_type> iterator;
    typedef ptrdiff_t difference_type;
    typedef sc_vector_base::size_type size_type;
    typedef object_type value_type;
    typedef object_type* pointer;
    typedef object_type& reference;

    //* todo: hide the sc_vector for the outside world
    sc_vector<object_type> objects;

    sc_map_base(const sc_module_name name);

    size_type size();
    iterator begin();
    iterator end();

    void make_sensitive(sc_sensitive& sensitive_list) const;
    //todo: void write_all(data_type value);

    //* todo: 2 trace functions one for vector and one for single signals
    //* todo: add the const to second argument of sc_trace
    template<typename trace_obj_type>
    friend void sc_trace(sc_trace_file* tf, sc_map_base<trace_obj_type>& sc_map, const std::string& name);

    friend class sc_map_iterator<object_type>;
};

#include "sc_map_base.cpp"

