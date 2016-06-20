/*!
 * @file sc_map_list.hpp
 * @author Christian Amstutz
 * @date September 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include <systemc.h>

#include <string>
#include <sstream>
#include <map>
#include "sc_map_list_range.hpp"

//******************************************************************************
template <typename key_value_T, typename object_T>
class sc_map_list : public sc_map_base<sc_map_list_range<key_value_T>, object_T>
{
public:
    typedef sc_map_base<sc_map_list_range<key_value_T>, object_T> base;
    typedef key_value_T key_value_type;
    typedef std::vector<key_value_type> key_value_vector_type;
    typedef typename base::range_type range_type;
    typedef typename base::key_type key_type;
    typedef typename base::key_vector_type key_vector_type;

    using base::bind;
    using base::operator();

    sc_map_list(const key_value_vector_type& key_vector, const sc_module_name name);
    template <typename config_T>
    sc_map_list(const key_value_vector_type& key_vector, const sc_module_name name, const config_T& configuration);
    sc_map_list(const range_type& new_range, const sc_module_name name);
    template <typename config_T>
    sc_map_list(const range_type& new_range, const sc_module_name name, const config_T& configuration);
    template <typename config_T>
    sc_map_list(const sc_module_name name, const std::map<key_value_T, config_T>& configuration);
    virtual ~sc_map_list() {};

    template <typename signal_T>
    void bind(sc_map_base<range_type, signal_T>& signal_map);
    template <typename signal_T>
    void operator()(sc_map_base<range_type, signal_T>& signal_map);
    // TODO: add binding for iterators, which are not in the correct order

    const char* kind() const;
};

//******************************************************************************

//******************************************************************************
template <typename key_value_T, typename object_T>
sc_map_list<key_value_T, object_T>::sc_map_list(const key_value_vector_type& key_vector,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range;

    for (typename key_value_vector_type::const_iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        range.add_key(key_type(*value_it));
    }

    this->init(range, typename base::creator());

    //simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
template <typename config_T>
sc_map_list<key_value_T, object_T>::sc_map_list(const key_value_vector_type& key_vector,
        const sc_module_name name, const config_T& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    range_type range;

    for (typename key_value_vector_type::const_iterator value_it = key_vector.begin();
         value_it != key_vector.end();
         ++value_it)
    {
        range.add_key(key_type(*value_it));
    }

    this->init(range, typename base::creator(), configuration);

//    simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
sc_map_list<key_value_T, object_T>::sc_map_list(const range_type& new_range,
        const sc_module_name name) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator());

    //simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
template <typename config_T>
sc_map_list<key_value_T, object_T>::sc_map_list(const range_type& new_range,
        const sc_module_name name, const config_T& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    this->init(new_range, typename base::creator(), configuration);

//  simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
template <typename config_T>
sc_map_list<key_value_T, object_T>::sc_map_list(const sc_module_name name,
        const std::map<key_value_T, config_T>& configuration) :
        sc_map_base<range_type, object_T>(name)
{
    key_vector_type new_range;
    std::vector<config_T> configuration_vec;

    for (typename std::map<key_value_T, config_T>::const_iterator single_config = configuration.begin();
         single_config != configuration.end();
         ++single_config)
    {
        new_range.push_back(key_type(single_config->first));
        configuration_vec.push_back(single_config->second);
    }

    this->init(new_range, typename base::creator(), configuration_vec);

//    simulation_size.add_sc_map(kind());

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
template <typename signal_T>
void sc_map_list<key_value_T, object_T>::bind(
        sc_map_base<range_type, signal_T>& signal_map)
{
    // todo: check for equal size
    // todo: check for same object
    // todo: check for compatibility of port and signal (pre-processor)

    for (typename sc_map_list<key_value_T, object_T>::iterator port_it = this->begin();
         port_it != this->end();
         ++port_it)
    {
        std::pair<bool, key_type> port_key = this->get_key(*port_it);
        if (port_key.first)
        {
            typename sc_map_list<key_value_T, signal_T>::object_type& signal = signal_map.at(port_key.second);
            port_it->bind(signal);
        }
        else
        {
            std::cerr << "sc_map_list.bind: Problem with iterator" << std::endl;
        }
    }

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
template <typename signal_T>
void sc_map_list<key_value_T, object_T>::operator()(
        sc_map_base<range_type, signal_T>& signal_map)
{
    bind(signal_map);

    return;
}

//******************************************************************************
template <typename key_value_T, typename object_T>
const char* sc_map_list<key_value_T, object_T>::kind() const
{
    return ("sc_map_list");
}
