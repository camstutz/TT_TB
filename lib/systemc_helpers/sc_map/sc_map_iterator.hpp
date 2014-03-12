/*!
 * @file sc_map_iterator.hpp
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

#include <iterator>

#include "sc_map_base.hpp"

template<typename object_type>
class sc_map_base;

//******************************************************************************
template<typename object_type>
class sc_map_iterator :
        public std::iterator<std::forward_iterator_tag, object_type>
{
public:
    typedef typename sc_map_base<object_type>::size_type size_type;

    virtual ~sc_map_iterator() {};

    bool operator==(const sc_map_iterator& other) const;
    bool operator!=(const sc_map_iterator& other) const;

    virtual sc_map_iterator& operator++ () =0;

    virtual object_type& operator* ();
    virtual object_type* operator-> ();

protected:
    sc_map_iterator(sc_map_base<object_type>& sc_map, size_type vect_pos=0);

    size_type get_vect_pos();
    void set_vect_pos(size_type vect_pos);

    sc_map_base<object_type>& sc_map;

private:
    size_type vect_pos;
};

//******************************************************************************
template<typename object_type>
bool sc_map_iterator<object_type>::operator==(const sc_map_iterator& other)
        const
{
    return (&sc_map.objects[vect_pos] == &other.sc_map.objects[other.vect_pos]);
}

//******************************************************************************
template<typename object_type>
bool sc_map_iterator<object_type>::operator!=(const sc_map_iterator& other)
        const
{
    return ( !(*this==other));
}

//******************************************************************************
template<typename object_type>
object_type& sc_map_iterator<object_type>::operator* ()
{
    // todo: ensure that out of range is not accessed (end iterator)
    return (sc_map.objects[vect_pos]);
}

//******************************************************************************
template<typename object_type>
object_type* sc_map_iterator<object_type>::operator-> ()
{
    return (&sc_map.objects[vect_pos]);
}

//******************************************************************************
template<typename object_type>
sc_map_iterator<object_type>::sc_map_iterator(sc_map_base<object_type>& sc_map,
        size_type vect_pos) :
        sc_map(sc_map),
        vect_pos(vect_pos)
{}

//******************************************************************************
template<typename object_type>
typename sc_map_iterator<object_type>::size_type
        sc_map_iterator<object_type>::get_vect_pos()
{
    return (vect_pos);
}

//******************************************************************************
template<typename object_type>
void sc_map_iterator<object_type>::set_vect_pos(size_type vect_pos)
{
    this->vect_pos = vect_pos;

    return;
}
