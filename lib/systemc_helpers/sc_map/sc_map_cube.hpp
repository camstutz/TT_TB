/*!
 * @file sc_map_cube.hpp
 * @author Christian Amstutz
 * @date Feb 19, 2014
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

#include <systemc.h>

#include "sc_map_base.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_cube : public sc_map_base<object_type>
{
public:
    typedef typename sc_map_base<object_type>::key_type key_type;
    typedef typename sc_map_base<object_type>::size_type size_type;

    static const key_type default_start_id_Z = 0;
    static const key_type default_start_id_Y = 0;
    static const key_type default_start_id_X = 0;

    sc_map_cube(const size_type element_cnt_Z, const size_type element_cnt_Y,
            const size_type element_cnt_X, const sc_module_name name = "",
            const key_type start_id_Z = default_start_id_Z,
            const key_type start_id_Y = default_start_id_Y,
            const key_type start_id_X = default_start_id_X);

    size_type size_Z();
    size_type size_Y();
    size_type size_X();

    object_type& at(const key_type key_Z, const key_type key_Y, const key_type key_X);

    template<typename signal_type>
    bool bind(sc_map_cube<signal_type>& signals_map);

private:
    // todo: make these const
    key_type start_id_Z;
    key_type start_id_Y;
    key_type start_id_X;

    std::map<key_type, std::map<key_type, std::map<key_type, object_type*> > > objects_map;

    class creator
    {
    public:
        size_type size_Z;
        size_type size_Y;
        size_type size_X;

        creator(const size_type size_Z, const size_type size_Y, const size_type size_X);
        object_type* operator() (const sc_module_name name, size_type id);
    };
};

#include "sc_map_cube.cpp"
