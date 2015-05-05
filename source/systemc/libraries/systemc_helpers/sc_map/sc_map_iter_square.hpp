/*!
 * @file sc_map_iter_square.hpp
 * @author Christian Amstutz
 * @date May 5, 2015
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
class sc_map_square;

//******************************************************************************
template <typename object_type>
class sc_map_iter_square : public sc_map_iterator<object_type>
{
    friend class sc_map_square<object_type>;

public:
    typedef sc_map_iterator<object_type> base;
    typedef typename sc_map_base<object_type>::key_type key_type;

    using base::operator=;

    virtual ~sc_map_iter_square() {};

    sc_map_iter_square& operator++ ();

private:
    typedef typename base::size_type size_type;

    using base::update_dim;

    sc_map_iter_square(sc_map_square<object_type>& sc_map,
            key_type start_Y, key_type stop_Y,
            key_type start_X, key_type stop_X);

    key_type Y_iter_start;
    key_type Y_iter_stop;
    key_type Y_pos;
    bool Y_up_cnt;
    key_type X_iter_start;
    key_type X_iter_stop;
    key_type X_pos;
    bool X_up_cnt;
};

//******************************************************************************
template <typename object_type>
sc_map_iter_square<object_type>&
        sc_map_iter_square<object_type>::operator++ ()
{
    sc_map_square<object_type>* sc_map_sq =
            dynamic_cast<sc_map_square<object_type>* >(this->sc_map);

    if (update_dim(X_pos, X_iter_start, X_iter_stop, X_up_cnt))
    {
        this->set_vect_pos(sc_map_sq->get_vect_pos(Y_pos, X_pos));
    }
    else
    {
        if (update_dim(Y_pos, Y_iter_start, Y_iter_stop, Y_up_cnt))
        {
            this->set_vect_pos(sc_map_sq->get_vect_pos(Y_pos, X_pos));
        }
        else
        {
            this->set_vect_pos(sc_map_sq->size());
        }
    }

    return *this;
}

//******************************************************************************
template <typename object_type>
sc_map_iter_square<object_type>::sc_map_iter_square(
        sc_map_square<object_type>& sc_map,
        key_type start_Y, key_type stop_Y,
        key_type start_X, key_type stop_X) :
        sc_map_iterator<object_type>(sc_map)
{
    sc_map_square<object_type>* sc_map_sq =
            dynamic_cast<sc_map_square<object_type>* >(this->sc_map);

    // Check validity
    key_type min_Y = sc_map_sq->start_id_Y;
    key_type max_Y = sc_map_sq->start_id_Y + sc_map_sq->size_Y()-1;
    key_type min_X = sc_map_sq->start_id_X;
    key_type max_X = sc_map_sq->start_id_X + sc_map_sq->size_X()-1;

    if (start_Y < min_Y) {start_Y = min_Y;}
    if (start_Y > max_Y) {start_Y = max_Y;}
    if (stop_Y < min_Y) {stop_Y = min_Y;}
    if (stop_Y > max_Y) {stop_Y = max_Y;}

    if (start_X < min_X) {start_X = min_X;}
    if (start_X > max_X) {start_X = max_X;}
    if (stop_X < min_X) {stop_X = min_X;}
    if (stop_X > max_X) {stop_X = max_X;}

    // Set values;
    Y_iter_start = start_Y;
    Y_iter_stop = stop_Y;
    Y_pos = start_Y;
    if (stop_Y >= start_Y)
    {
        Y_up_cnt = true;
    }
    else
    {
        Y_up_cnt = false;
    }

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

    size_type start_pos = sc_map_sq->get_vect_pos(Y_pos, X_pos);
    this->set_vect_pos(start_pos);

    return;
}
