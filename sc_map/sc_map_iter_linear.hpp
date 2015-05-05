/*!
 * @file sc_map_iter_linear.hpp
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

#include "sc_map_base.hpp"
#include "sc_map_iterator.hpp"

template <typename object_type>
class sc_map_linear;

//******************************************************************************
template <typename object_type>
class sc_map_iter_linear : public sc_map_iterator<object_type>
{
    friend class sc_map_linear<object_type>;

public:
    typedef sc_map_iterator<object_type> base;
    typedef typename sc_map_base<object_type>::key_type key_type;

    using base::operator=;

    virtual ~sc_map_iter_linear() {};

    sc_map_iter_linear& operator++ ();

private:
    typedef typename base::size_type size_type;

    using base::update_dim;

    sc_map_iter_linear(sc_map_linear<object_type>& sc_map,
            key_type start_X, key_type stop_X);

    key_type X_iter_start;
    key_type X_iter_stop;
    key_type X_pos;
    bool X_up_cnt;
};

//******************************************************************************
template <typename object_type>
sc_map_iter_linear<object_type>&
        sc_map_iter_linear<object_type>::operator++ ()
{
    sc_map_linear<object_type>* sc_map_lin =
            dynamic_cast<sc_map_linear<object_type>* >(this->sc_map);

    if (update_dim(X_pos, X_iter_start, X_iter_stop, X_up_cnt))
    {
        this->set_vect_pos(sc_map_lin->get_vect_pos(X_pos));
    }
    else
    {
        this->set_vect_pos(sc_map_lin->size());
    }

    return *this;
}

//******************************************************************************
template <typename object_type>
sc_map_iter_linear<object_type>::sc_map_iter_linear(
        sc_map_linear<object_type>& sc_map,
        key_type start_X, key_type stop_X) :
        sc_map_iterator<object_type>(sc_map)
{
    sc_map_linear<object_type>* sc_map_lin =
            dynamic_cast<sc_map_linear<object_type>* >(this->sc_map);

    // Check validity
    key_type min_X = sc_map_lin->start_id_X;
    key_type max_X = sc_map_lin->start_id_X + sc_map_lin->size_X()-1;

    if (start_X < min_X) {start_X = min_X;}
    if (start_X > max_X) {start_X = max_X;}

    if (stop_X < min_X) {stop_X = min_X;}
    if (stop_X > max_X) {stop_X = max_X;}

    // Set values;
    X_iter_start = start_X;
    X_iter_stop = stop_X;
    X_pos = start_X;
    if (stop_X >= start_X)
    {
        X_up_cnt = true;
    }
    else
    {
        X_up_cnt = false;
    }

    size_type start_pos = sc_map_lin->get_vect_pos(X_pos);
    this->set_vect_pos(start_pos);

    return;
}
