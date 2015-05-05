/*!
 * @file sc_map_iter_sequential.hpp
 * @author Christian Amstutz
 * @date April 30, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_iterator.hpp"

template<typename object_type>
class sc_map_base;

//******************************************************************************
template<typename object_type>
class sc_map_iter_sequential : public sc_map_iterator<object_type>
{
    friend class sc_map_base<object_type>;

public:
    virtual ~sc_map_iter_sequential() {};

    virtual sc_map_iter_sequential& operator++ ();

private:
    typedef typename sc_map_iterator<object_type>::size_type size_type;

    sc_map_iter_sequential(sc_map_base<object_type>& sc_map, size_type pos);
};


//******************************************************************************
template<typename object_type>
sc_map_iter_sequential<object_type>&
        sc_map_iter_sequential<object_type>::operator++ ()
{
    size_type new_pos = sc_map_iterator<object_type>::get_vect_pos();
    ++new_pos;
    sc_map_iterator<object_type>::set_vect_pos(new_pos);

    return *this;
}

//******************************************************************************
template<typename object_type>
sc_map_iter_sequential<object_type>::sc_map_iter_sequential(
        sc_map_base<object_type>& sc_map, size_type pos) :
        sc_map_iterator<object_type>(sc_map, pos)
{}
