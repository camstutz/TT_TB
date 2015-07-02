/*!
 * @file sc_map_base.hpp
 * @author Christian Amstutz
 * @date June 18, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_iterator.hpp"
#include "sc_map_config.hpp"

#include "../modelsim_support/modelsim_support.hpp"

#include <systemc.h>

#include <vector>
#include <map>
#include <string>
#include <sstream>

//******************************************************************************
template <typename range_T, typename object_T>
class sc_map_base : public sc_object
{
    friend class sc_map_iterator<sc_map_base<range_T, object_T> >;

public:
    typedef range_T range_type;
    typedef typename range_type::key_type key_type;
    typedef std::vector<key_type> key_vector_type;
    typedef object_T object_type;
    typedef std::map<key_type, object_type*, typename key_type::Comperator> map_type;
    typedef sc_map_iterator<sc_map_base<range_type, object_type> > iterator;
    typedef typename map_type::size_type size_type;
    typedef object_type* pointer;

    sc_map_base(const sc_module_name name);
    virtual ~sc_map_base() {};

    iterator begin();
    iterator end();

    range_type* get_range() const;
    std::pair<bool, key_type> get_key(object_type& object) const;

    //* todo: const versions needed?
    object_type& at(const key_type& key);
    object_type& operator[] (const key_type& key);
    iterator operator()(const key_type& start_key, const key_type& end_key);
    iterator operator()(const sc_map_range<key_type>& range);

    template <typename signal_type>
    void bind(sc_signal<signal_type>& signal);
    template <typename signal_type>
    void operator()(sc_signal<signal_type>& signal);
    template <typename signal_range_T, typename signal_T>
    void bind(sc_map_base<signal_range_T, signal_T>& signal_map);
    template <typename signal_range_T, typename signal_T>
    void operator()(sc_map_base<signal_range_T, signal_T>& signal_map);
    template <typename signal_map_T>
    void bind(sc_map_iterator<signal_map_T> signal_it);
    template <typename signal_map_T>
    void operator()(sc_map_iterator<signal_map_T> signal_it);

    template<typename data_type>
    void write(const data_type& value);
// todo: allow operator assignment to multiple ports
//    template<typename data_type>
//    void operator=(const data_type& value);

    /** Function for tracing support in ModelSim */
    #ifdef MODELSIM_COMPILER
        template <typename data_type>
        void register_signal_modelsim();
    #endif

public:
    template <typename Creator>
    void init(const range_type& new_range, const Creator& object_creator);
    template <typename Creator, typename config_type>
    void init(const range_type& new_range, const Creator& object_creator, const config_type& configurator);
    template <typename Creator, typename config_type>
    void init(const range_type& new_range, const Creator& object_creator, const std::vector<config_type>& configurations);
    template <typename Creator, typename config_type>
    void init(const range_type& new_range, const Creator& object_creator, const std::map<key_type, config_type>& configurations);

    map_type objects;
    range_type range;

    class creator
    {
    public:
        creator() {};
        object_type* operator() (const sc_module_name name, const sc_map_base<range_type, object_type>::key_type& id) const;
        template <typename config_T>
        object_type* operator() (const sc_module_name name, const sc_map_base<range_type, object_type>::key_type& id, const config_T& configuration) const;
    };

//* todo: add const to second argument of sc_trace
template <typename trace_range_T, typename trace_object_T>
friend void sc_trace(sc_trace_file* tf, sc_map_base<trace_range_T, trace_object_T>& sc_map, const std::string& name);

template <typename signal_range_T, typename signal_T>
friend sc_sensitive& operator<< (sc_sensitive& sensitivity_list, sc_map_base<signal_range_T, signal_T>& signal_map);

};

//******************************************************************************

//******************************************************************************
template <typename range_T, typename object_T>
sc_map_base<range_T, object_T>::sc_map_base(const sc_module_name name) :
        sc_object(name)
{}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename Creator>
void sc_map_base<range_T, object_T>::init(const range_type& new_range,
        const Creator& object_creator)
{
    range = new_range;

    key_vector_type key_vector = range.get_key_vector();
    for (typename key_vector_type::const_iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it);
        objects.insert(typename map_type::value_type(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<range_T, object_T>::init(const range_type& new_range,
        const Creator& object_creator,
        const config_type& configurator)
{
    range = new_range;

    key_vector_type key_vector = range.get_key_vector();
    for (typename key_vector_type::const_iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, configurator);
        objects.insert(typename map_type::value_type(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<range_T, object_T>::init(const range_type& new_range,
        const Creator& object_creator,
        const std::vector<config_type>& configurations)
{
    range = new_range;

    key_vector_type key_vector = range.get_key_vector();
    typename std::vector<config_type>::const_iterator config_it = configurations.begin();
    for (typename key_vector_type::const_iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, *config_it);
        objects.insert(typename map_type::value_type(*key_it, p));

        ++config_it;
    }

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename Creator, typename config_type>
void sc_map_base<range_T, object_T>::init(const range_type& new_range,
        const Creator& object_creator,
        const std::map<key_type, config_type>& configurations)
{
    range = new_range;

    key_vector_type key_vector = range.get_key_vector();
    for (typename key_vector_type::const_iterator key_it = key_vector.begin();
         key_it != key_vector.end();
         ++key_it)
    {
        std::string name = basename();
        const char* cname = name.c_str();

        object_type* p = object_creator(cname, *key_it, configurations.at(*key_it));
        objects.push_back(map_type::value_type(*key_it, p));
    }

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::iterator
        sc_map_base<range_T, object_T>::begin()
{
    return iterator(this);
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::iterator
        sc_map_base<range_T, object_T>::end()
{
    return iterator(this, iterator::end);
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::range_type*
        sc_map_base<range_T, object_T>::get_range() const
{
    return new range_type(range);
}

//******************************************************************************
template <typename range_T, typename object_T>
std::pair<bool, typename sc_map_base<range_T, object_T>::key_type>
        sc_map_base<range_T, object_T>::get_key(object_type& object) const
{
    std::pair<bool, key_type> key_pair;
    key_pair.first = false;

    for (typename map_type::const_iterator object_it = objects.begin();
         object_it != objects.end();
         ++object_it)
    {
        if (object_it->second == &object)
        {
            key_pair.first = true;
            key_pair.second = object_it->first;
            break;
        }
    }

    return key_pair;
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::object_type&
        sc_map_base<range_T, object_T>::at(const key_type& key)
{
    // todo: at exception handling for out range accesses
    object_type& ret_object = *(this->objects[key]);

    return ret_object;
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::object_type&
        sc_map_base<range_T, object_T>::operator[] (const key_type& key)
{
    return at(key);
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::iterator
        sc_map_base<range_T, object_T>::operator()(
        const key_type& start_key, const key_type& end_key)
{
    return iterator(this, start_key, end_key);
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::iterator
sc_map_base<range_T, object_T>::operator()(const sc_map_range<key_type>& range)
{
    return iterator(this, range);
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename signal_T>
void sc_map_base<range_T, object_T>::bind(sc_signal<signal_T>& signal)
{
    for (iterator port_it = begin(); port_it != end(); ++port_it)
    {
        port_it->bind(signal);
    }

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename signal_T>
void sc_map_base<range_T, object_T>::operator()(sc_signal<signal_T>& signal)
{
    bind(signal);

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename signal_range_T, typename signal_T>
void sc_map_base<range_T, object_T>::bind(sc_map_base<signal_range_T, signal_T>&
        signal_map)
{
    bind(signal_map.begin());

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename signal_range_T, typename signal_T>
void sc_map_base<range_T, object_T>::operator()(
        sc_map_base<signal_range_T, signal_T>& signal_map)
{
    bind(signal_map);

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename signal_map_T>
void sc_map_base<range_T, object_T>::bind(sc_map_iterator<signal_map_T> signal_it)
{
    // todo: check for equal size
    // todo: check for same object
    // todo: check for compatibility of port and signal (pre-processor)

    for (iterator port_it = this->begin();
         port_it != this->end();
         ++port_it)
    {
        port_it->bind(*signal_it);

        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename signal_map_T>
void sc_map_base<range_T, object_T>::operator()(
        sc_map_iterator<signal_map_T> signal_it)
{
    bind(signal_it);

    return;
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename data_type>
void sc_map_base<range_T, object_T>::write(const data_type& value)
{
    for (iterator object_it = begin(); object_it != end(); ++object_it)
    {
        object_it->write(value);
    }

    return;
}

////******************************************************************************
//template <typename range_T, typename object_T>
//template<typename data_type>
//void sc_map_base<key_T, range_T, object_T>::operator= (const data_type value)
//{
//    write(value);
//
//    return;
//}

//******************************************************************************
template <typename trace_range_T, typename trace_object_T>
void sc_trace(sc_trace_file* tf, sc_map_base<trace_range_T, trace_object_T>&
        sc_map, const std::string& name)
{
    for (typename sc_map_base<trace_range_T, trace_object_T>::iterator object_it = sc_map.begin();
         object_it != sc_map.end();
         ++object_it)
    {
        std::stringstream full_name;
        full_name << name
                  << sc_map::key_separator_char
                  << object_it.get_key().second;
        sc_trace(tf, *object_it, full_name.str().c_str());
    }

    return;
}

//******************************************************************************
template <typename signal_range_T, typename signal_T>
sc_sensitive& operator<< (sc_sensitive& sensitivity_list,
        sc_map_base<signal_range_T, signal_T>& signal_map)
{
    for (typename sc_map_base<signal_range_T, signal_T>::iterator signal_it = signal_map.begin();
         signal_it != signal_map.end();
         ++signal_it)
    {
        sensitivity_list << *signal_it;
    }

    return sensitivity_list;
}

//******************************************************************************
template <typename range_T, typename object_T>
typename sc_map_base<range_T, object_T>::object_type*
        sc_map_base<range_T, object_T>::creator::operator() (
        const sc_module_name name,
        const sc_map_base<range_type, object_type>::key_type& id) const
{
    std::stringstream full_name;

    full_name << name << sc_map::key_separator_char << id;

    return (new object_type(full_name.str().c_str()) );
}

//******************************************************************************
template <typename range_T, typename object_T>
template <typename config_T>
typename sc_map_base<range_T, object_T>::object_type*
        sc_map_base<range_T, object_T>::creator::operator() (
        const sc_module_name name,
        const sc_map_base<range_type, object_type>::key_type& id,
        const config_T& configuration) const
{
    std::stringstream full_name;

    full_name << name << sc_map::key_separator_char << id;

    return (new object_type(full_name.str().c_str(), configuration));
}

//// *****************************************************************************
//#ifdef MODELSIM_COMPILER
//
//template <typename range_T, typename object_T>
//template <typename data_type>
//void sc_map_base<key_T, range_T, object_T>::register_signal_modelsim()
//{
//    const_container_iterator object_it = objects.begin();
//    for (; object_it != objects.end(); ++object_it)
//    {
//        SC_MTI_REGISTER_CUSTOM_DEBUG(*object_it, data_type::get_max_value_length(), data_type::mti_debug_cb);
//    }
//
//    return;
//}
//
//#endif
