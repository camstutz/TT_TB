/*!
 * @file sc_map_base.hpp
 * @author Christian Amstutz
 * @date June 4, 2014
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
#include <sstream>

#include <systemc.h>

#include "sc_map_iter_sequential.hpp"
#include "../modelsim_support/modelsim_support.hpp"

//* todo: add access operators [] .at()

//******************************************************************************
template<typename object_type>
class sc_map_base : public sc_object
{
public:
    typedef std::vector<object_type*> container_type;
    typedef typename container_type::iterator container_iterator;
    typedef typename container_type::const_iterator const_container_iterator;
    typedef int key_type;
    typedef sc_map_iter_sequential<object_type> iterator;
    typedef ptrdiff_t difference_type;
    typedef typename container_type::size_type size_type;
    typedef object_type value_type;
    typedef object_type* pointer;
    typedef object_type& reference;

    //* todo: hide objects to the outside world
    container_type objects;

    sc_map_base(const sc_module_name name);
    virtual ~sc_map_base() {};

    // todo: add simple init with just number
    //void init( size_type n )
    //    { init( n, &sc_map_base<object_type>::create_element ); }

    template<typename Creator>
    void init(size_type n, Creator object_creator);

    size_type size();
    iterator begin();
    iterator end();

    template<typename signal_type>
    void bind(sc_map_base<signal_type> signal_map);
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

    /** Function for tracing support in ModelSim */
#ifdef MODELSIM_COMPILER
    template<typename data_type>
    void register_signal_modelsim();
#endif

    friend class sc_map_iterator<object_type>;
};

//******************************************************************************

//******************************************************************************
template<typename object_type>
sc_map_base<object_type>::sc_map_base(const sc_module_name name) :
        sc_object(name)
{}

//******************************************************************************
template<typename object_type>
template<typename Creator>
void sc_map_base<object_type>::init(size_type n, Creator object_creator)
{
    // check correct call conditions
//    if (!n)
//      return false;
//
//    if( size() ) // already filled
//    {
//      std::stringstream str;
//      str << name()
//          << ", size=" << size()
//          << ", requested size=" << n;
//      SC_REPORT_ERROR( SC_ID_VECTOR_INIT_CALLED_TWICE_
//                     , str.str().c_str() );
//      return false;

    objects.reserve(n);
    for (size_type i = 0; i<n; ++i)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, i);
        objects.push_back(p);
    }

    return;
}

//******************************************************************************
template<typename object_type>
typename sc_map_base<object_type>::size_type sc_map_base<object_type>::size()
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
template<typename signal_type>
void sc_map_base<object_type>::bind(sc_map_base<signal_type> signal_map)
{
    // todo: check range

    iterator port_it = begin();
    iterator port_end = end();
    typename sc_map_base<signal_type>::iterator signal_it = signal_map.begin();
    typename sc_map_base<signal_type>::iterator signal_end = signal_map.end();

    for (; port_it != port_end; ++port_it)
    {
        port_it->bind(*signal_it);
        ++signal_it;
    }

    return;
}

//******************************************************************************
template<typename object_type>
template<typename signal_type>
bool sc_map_base<object_type>::bind_by_iter(sc_map_iterator<object_type>& port_iter,
        sc_map_iterator<signal_type>& signal_iter)
{
    // todo: check for equal size
    // todo: check for same object
    // todo: check for compatibility of port and signal (pre-processor)

    iterator end = this->end();
    for ( ; port_iter != end; ++port_iter)
    {
        port_iter->bind(*signal_iter);
        ++signal_iter;
    }

    return (true);
}

//******************************************************************************
template<typename object_type>
template<typename signal_type>
bool sc_map_base<object_type>::bind_by_iter(sc_map_iterator<signal_type>& signal_iter)
{
    iterator port_iter = this->begin();
    bool bind_ok = bind_by_iter(port_iter, signal_iter);

    return (bind_ok);
}

//******************************************************************************
template<typename object_type>
void sc_map_base<object_type>::make_sensitive(
        sc_sensitive& sensitive_list) const
{
    // todo: change it to a traditional way of sensitivity lists
    // todo: make it possible to react on other than pos
    // todo: make it not to use the reference, but const
    const_container_iterator object_it = objects.begin();
    for (; object_it != objects.end(); ++object_it)
    {
        sensitive_list << **object_it;
    }

    return;
}

//******************************************************************************
template<typename object_type>
template<typename data_type>
void sc_map_base<object_type>::write_all(const data_type& value)
{
    container_iterator object_it = objects.begin();
    for(; object_it != objects.end(); ++object_it)
    {
        (*object_it)->write(value);
    }

    return;
}

//******************************************************************************
template<typename trace_obj_type>
void sc_trace(sc_trace_file* tf, sc_map_base<trace_obj_type>& sc_map, const std::string& name)
{
    typename sc_map_base<trace_obj_type>::iterator object_it = sc_map.begin();
    for (; object_it != sc_map.end(); ++object_it)
    {
        std::stringstream full_name;
        full_name << name << "." << object_it->name();
        sc_trace(tf, *object_it, full_name.str().c_str());
    }

    return;
}

// *****************************************************************************
#ifdef MODELSIM_COMPILER

template <typename object_type>
template <typename data_type>
void sc_map_base<object_type>::register_signal_modelsim()
{
    const_container_iterator object_it = objects.begin();
    for (; object_it != objects.end(); ++object_it)
    {
        SC_MTI_REGISTER_CUSTOM_DEBUG(*object_it, data_type::get_max_value_length(), data_type::mti_debug_cb);
    }
    
    return;
}

#endif
