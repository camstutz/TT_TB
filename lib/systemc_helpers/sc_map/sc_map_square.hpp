/*!
 * @file sc_map_square.hpp
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

#include <systemc.h>

#include "sc_map_base.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_square : public sc_map_base<object_type>
{
public:
    typedef typename sc_map_base<object_type>::key_type key_type;
    typedef struct
    {
        key_type Y_dim;
        key_type X_dim;
    } full_key_type;
    typedef typename sc_map_base<object_type>::size_type size_type;

    static const key_type default_start_id_Y = 0;
    static const key_type default_start_id_X = 0;

    sc_map_square(const size_type element_cnt_Y,
            const size_type element_cnt_X, const sc_module_name name = "",
            const key_type start_id_Y = default_start_id_Y,
            const key_type start_id_X = default_start_id_X);

    size_type size_Y();
    size_type size_X();

    object_type& at(const key_type key_Y, const key_type key_X);
    std::pair<bool, full_key_type> get_key(object_type& object) const;

    template<typename signal_type>
    bool bind(sc_map_square<signal_type>& signals_map);

private:
    key_type start_id_Y;
    key_type start_id_X;

    std::map<key_type, std::map<key_type, object_type*> > objects_map;

    class creator
    {
    public:
        size_type size_Y;
        size_type size_X;

        creator(const size_type size_Y, const size_type size_X);
        object_type* operator() (const sc_module_name name, size_type id);
    };
};

#include "sc_map_square.cpp"
