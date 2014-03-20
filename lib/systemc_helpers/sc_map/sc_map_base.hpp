/*!
 * @file sc_map_base.hpp
 * @author Christian Amstutz
 * @date Mar 11, 2014
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
    typedef sc_map_iter_sequential<object_type> iterator;
    typedef ptrdiff_t difference_type;
    typedef sc_vector_base::size_type size_type;
    typedef object_type value_type;
    typedef object_type* pointer;
    typedef object_type& reference;

    //* todo: hide the sc_vector for the outside world
    sc_vector<object_type> objects;

    sc_map_base(const sc_module_name name);
    virtual ~sc_map_base() {};

    size_type size();
    iterator begin();
    iterator end();

    // todo: how to access members of modules over which is iterated
    // todo: single signal to many port binding
    template<typename signal_type>
    bool bind_by_iter(sc_map_iterator<object_type>& port_iter, sc_map_iterator<signal_type>& signal_iter);
    template<typename signal_type>
    bool bind_by_iter(sc_map_iterator<signal_type>& signal_iter);

    void make_sensitive(sc_sensitive& sensitive_list) const;
    template<typename data_type>
    void write_all(const data_type& value);
    //template<typename data_type>
    // todo: void write_range(data_type value);

    //* todo: add const to second argument of sc_trace
    template<typename trace_obj_type>
    friend void sc_trace(sc_trace_file* tf, sc_map_base<trace_obj_type>& sc_map, const std::string& name);

    friend class sc_map_iterator<object_type>;
};

#include "sc_map_base.cpp"

