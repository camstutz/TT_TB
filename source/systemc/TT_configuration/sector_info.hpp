/*!
 * @file sector_info.hpp
 * @author Christian Amstutz
 * @date October 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/frontend/sensor_module/sensor_module_address.hpp"
#include "local_module_address.hpp"

#include <set>
#include <map>
#include <ostream>
#include <iostream>
#include <utility>

// *****************************************************************************
/*!
 * @brief
 */
class sector_info
{
public:
    typedef unsigned int layer_t;
    typedef unsigned int ladder_t;
    //typedef unsigned int layer_ladder_t;
    typedef unsigned int module_t;

    unsigned int id;
    unsigned int eta;
    unsigned int phi;

    sector_info();
    sector_info(const unsigned int id, const unsigned int eta, const unsigned int phi);

    bool operator== (const sector_info& rhs) const;
    bool operator< (const sector_info& rhs) const;

    void add_modules(const sensor_module_address& module_address);
    std::pair<bool, local_module_address> get_local_address(sensor_module_address global_address);

    void print_layers();
    void print_ladders();
    void print_modules();

private:
    typedef std::set<layer_t> layer_set_t;
    typedef std::map<layer_t, std::set<ladder_t> > ladder_set_t;
    typedef std::map<layer_t, std::map< ladder_t, std::set<module_t> > > module_set_t;

    layer_set_t layers;
    ladder_set_t ladders;
    module_set_t modules;

    template<typename T>
    typename std::set<T>::iterator first_in_set(const std::set<T>& test_set) const;
    template<typename T>
    typename std::set<T>::iterator next_in_set(const std::set<T>& test_set, const typename std::set<T>::iterator& actual_pos) const;

    friend std::ostream& operator<< (std::ostream &os, sector_info const &v);
};
