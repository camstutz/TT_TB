/*!
 * @file sc_map_iter_square.hpp
 * @author Christian Amstutz
 * @date Mar 12, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "sc_map_base.hpp"
#include "sc_map_square.hpp"
#include "sc_map_iterator.hpp"

//******************************************************************************
template<typename object_type>
class sc_map_square;

//******************************************************************************
template<typename object_type>
class sc_map_iter_square : public sc_map_iterator<object_type>
{
public:
    typedef typename sc_map_base<object_type>::key_type key_type;
    typedef typename sc_map_iterator<object_type>::size_type size_type;

    virtual ~sc_map_iter_square() {};

    sc_map_iter_square& operator++ ();

private:
    sc_map_iter_square(sc_map_square<object_type>& sc_map,
            key_type start_Y, key_type stop_Y, bool iterate_Y,
            key_type start_X, key_type stop_X, bool iterate_X);

    const key_type Y_iter_start;
    const key_type Y_iter_stop;
    key_type Y_pos;
    const bool iterate_Y;
    const key_type X_iter_start;
    const key_type X_iter_stop;
    key_type X_pos;
    const bool iterate_X;

    friend class sc_map_square<object_type>;
};

//******************************************************************************
template<typename object_type>
sc_map_iter_square<object_type>&
        sc_map_iter_square<object_type>::operator++ ()
{
    sc_map_square<object_type>* sc_map_sq = dynamic_cast<sc_map_square<object_type>* >(this->sc_map);

    if (iterate_X)
    {
        ++X_pos;
        if(X_pos <= X_iter_stop)
        {
            this->set_vect_pos(sc_map_sq->get_vect_pos(Y_pos, X_pos));
            return (*this);
        }
    }

    ++Y_pos;
    if (Y_pos > Y_iter_stop)
    {
        this->set_vect_pos(sc_map_sq->size());
        return (*this);
    }

    if (iterate_Y)
    {
        X_pos = X_iter_start;
        this->set_vect_pos(sc_map_sq->get_vect_pos(Y_pos, X_pos));
        return (*this);
    }
    else
    {
        this->set_vect_pos(sc_map_sq->size());
        return (*this);
    }
}

//******************************************************************************
template<typename object_type>
sc_map_iter_square<object_type>::sc_map_iter_square(
        sc_map_square<object_type>& sc_map,
        key_type start_Y, key_type stop_Y, bool iterate_Y,
        key_type start_X, key_type stop_X, bool iterate_X) :
        sc_map_iterator<object_type>(sc_map),
        Y_iter_start(start_Y),
        Y_iter_stop(stop_Y),
        Y_pos(start_Y),
        iterate_Y(iterate_Y),
        X_iter_start(start_X),
        X_iter_stop(stop_X),
        X_pos(start_X),
        iterate_X(iterate_X)
{
    sc_map_square<object_type>* sc_map_sq =
            dynamic_cast<sc_map_square<object_type>* >(this->sc_map);

    if ( (sc_map_sq->start_id_Y+sc_map_sq->size_Y() <= Y_pos) ||
            (sc_map_sq->start_id_X+sc_map_sq->size_X() <= X_pos) )
    {
        // todo: warning ?
        this->set_vect_pos(sc_map_sq->size());
    }
    else if ( (sc_map_sq->start_id_Y > Y_pos) ||
            (sc_map_sq->start_id_X > X_pos) )
    {
        // todo: this is probably not the best solution: probably range checking --> warning
        // todo: if only one coordinate is wrong put it to beginning of dimension
        this->set_vect_pos(0);
    }
    else
    {
        size_type new_pos = sc_map_sq->get_vect_pos(Y_pos, X_pos);
        this->set_vect_pos(new_pos);
    }

    return;
}
