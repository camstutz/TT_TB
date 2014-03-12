/*!
 * @file sc_map_cube.hpp
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

#include <string>
#include <map>

#include <systemc.h>

#include "sc_map_base.hpp"
#include "sc_map_iter_cube.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_cube : public sc_map_base<object_type>
{
public:
    typedef typename sc_map_base<object_type>::key_type key_type;
    typedef struct
    {
        key_type Z_dim;
        key_type Y_dim;
        key_type X_dim;
    } full_key_type;
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
    std::pair<bool, full_key_type> get_key(object_type& object) const;

    sc_map_iter_cube<object_type> begin_partial(
            const key_type pos_Z, const bool iterate_Z,
            const key_type pos_Y, const bool iterate_Y,
            const key_type pos_X, const bool iterate_X);
    sc_map_iter_cube<object_type> begin_partial(
            const key_type start_Z, const key_type stop_Z, const bool iterate_Z,
            const key_type start_Y, const key_type stop_Y, const bool iterate_Y,
            const key_type start_X, const key_type stop_X, const bool iterate_X);

    template<typename signal_type>
    bool bind(sc_map_cube<signal_type>& signals_map);

private:
    const key_type start_id_Z;
    const key_type start_id_Y;
    const key_type start_id_X;

    std::map<key_type, std::map<key_type, std::map<key_type, size_type> > > objects_map;

    size_type get_vect_pos(key_type pos_Z, key_type pos_Y, key_type pos_X);

    class creator
    {
    public:
        size_type size_Z;
        size_type size_Y;
        size_type size_X;

        creator(const size_type size_Z, const size_type size_Y, const size_type size_X);
        object_type* operator() (const sc_module_name name, size_type id);
    };

    friend class sc_map_iter_cube<object_type>;
};

#include "sc_map_cube.cpp"
