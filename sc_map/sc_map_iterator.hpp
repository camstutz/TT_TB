/*!
 * @file sc_map_iterator.hpp
 * @author Christian Amstutz
 * @date May 21, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <iterator>

#include <systemc.h>

template<typename key_T, typename object_T>
class sc_map_base;

//template<typename object_type>
//class sc_map_iter_linear;

//template<typename object_type>
//class sc_map_iter_square;
//
//template<typename object_type>
//class sc_map_iter_cube;
//
//template<typename object_type>
//class sc_map_iter_4d;

//******************************************************************************
template<typename sc_map_T>
class sc_map_iterator : public std::iterator<std::forward_iterator_tag, sc_map_T::object_type>
{
public:
    typedef sc_map_T map_type;
    typedef typename map_type::object_type object_type;
    typedef typename map_type::key_type key_type;
    typedef sc_map_base<key_type, object_type> base_map_type;

    virtual ~sc_map_iterator() {};

    bool operator==(const sc_map_iterator& other) const;
    bool operator!=(const sc_map_iterator& other) const;

    virtual sc_map_iterator& operator++ () =0;

    virtual object_type& operator* ();
    virtual object_type* operator-> ();

    template<typename data_type>
    void write(const data_type& value);
    template<typename data_type>
    void operator= (const data_type& value);

//    template <typename signal_type>
//    void bind(sc_signal<signal_type>& signal);
//    template <typename signal_type>
//    void operator() (sc_signal<signal_type>& signal);
//    template <typename signal_type>
//    void bind(sc_map_base<signal_type>& signal_map);
//    template <typename signal_type>
//    void operator() (sc_map_base<signal_type>& signal_map);
//    template <typename signal_type>
//    void bind(sc_map_iterator<signal_type>& signal_it);
//    template <typename signal_type>
//    void operator() (sc_map_iterator<signal_type>& signal_it);
//
//    template <typename signal_type>
//    void bind(sc_map_iter_linear<signal_type> signal_it);
//    template <typename signal_type>
//    void operator() (sc_map_iter_linear<signal_type> signal_it);
//    template <typename signal_type>
//    void bind(sc_map_iter_square<signal_type> signal_it);
//    template <typename signal_type>
//    void operator() (sc_map_iter_square<signal_type> signal_it);
//    template <typename signal_type>
//    void bind(sc_map_iter_cube<signal_type> signal_it);
//    template <typename signal_type>
//    void operator() (sc_map_iter_cube<signal_type> signal_it);
//    template <typename signal_type>
//    void bind(sc_map_iter_4d<signal_type> signal_it);
//    template <typename signal_type>
//    void operator() (sc_map_iter_4d<signal_type> signal_it);

protected:
    typedef typename base_map_type::size_type size_type;
    typedef bool cnt_direction_t;

    static const cnt_direction_t up;
    static const cnt_direction_t down;

    base_map_type* sc_map;

    sc_map_iterator(base_map_type& sc_map, size_type vect_pos = 0);

    size_type get_vect_pos();
    void set_vect_pos(size_type vect_pos);

    bool update_dim(key_type& key, const key_type key_start, const key_type key_stop, const cnt_direction_t direction);

private:
    size_type vect_pos;
};

//******************************************************************************

//******************************************************************************

template<typename sc_map_T>
const typename sc_map_iterator<sc_map_T>::cnt_direction_t sc_map_iterator<sc_map_T>::up = true;

template<typename sc_map_T>
const typename sc_map_iterator<sc_map_T>::cnt_direction_t
        sc_map_iterator<sc_map_T>::down = false;

//******************************************************************************
template<typename sc_map_T>
bool sc_map_iterator<sc_map_T>::operator==(const sc_map_iterator& other)
        const
{
    return (sc_map->objects[vect_pos] == other.sc_map->objects[other.vect_pos]);
}

//******************************************************************************
template<typename sc_map_T>
bool sc_map_iterator<sc_map_T>::operator!=(const sc_map_iterator& other) const
{
    return !(*this==other);
}

//******************************************************************************
template<typename sc_map_T>
typename sc_map_iterator<sc_map_T>::object_type&
        sc_map_iterator<sc_map_T>::operator* ()
{
    // todo: ensure that out of range is not accessed (end iterator)
    return (*sc_map->objects[vect_pos]);
}

//******************************************************************************
template<typename sc_map_T>
typename sc_map_iterator<sc_map_T>::object_type*
        sc_map_iterator<sc_map_T>::operator-> ()
{
    return (sc_map->objects[vect_pos]);
}

//******************************************************************************
template<typename sc_map_T>
template<typename data_type>
void sc_map_iterator<sc_map_T>::write(const data_type& value)
{
    for (; *this != sc_map->end(); ++(*this))
    {
        (**this).write(value);
    }

    return;
}

//******************************************************************************
template<typename sc_map_T>
template<typename data_type>
void sc_map_iterator<sc_map_T>::operator= (const data_type& value)
{
    write(value);

    return;
}

////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_signal<signal_type>& signal)
//{
//    for (; *this != sc_map->end(); ++(*this))
//    {
//        (**this).bind(signal);
//    }
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_signal<signal_type>& signal)
//{
//    bind(signal);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_map_base<signal_type>& signal_map)
//{
//    typename sc_map_base<signal_type>::iterator signal_it = signal_map.begin();
//    for (; *this != sc_map->end(); ++(*this))
//    {
//        (**this).bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_map_base<signal_type>&
//        signal_map)
//{
//    bind(signal_map);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_map_iterator<signal_type>& signal_it)
//{
//    for (; *this != sc_map->end(); ++(*this))
//    {
//        (**this).bind(*signal_it);
//
//        ++signal_it;
//    }
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_map_iterator<signal_type>&
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_map_iter_linear<signal_type>
//        signal_it)
//{
//    sc_map_iterator<signal_type> *sig_map_it = &signal_it;
//    bind(*sig_map_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_map_iter_linear<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_map_iter_square<signal_type>
//        signal_it)
//{
//    sc_map_iterator<signal_type> *sig_map_it = &signal_it;
//    bind(*sig_map_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_map_iter_square<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_map_iter_cube<signal_type> signal_it)
//{
//    sc_map_iterator<signal_type> *sig_map_it = &signal_it;
//    bind(*sig_map_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_map_iter_cube<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::bind(sc_map_iter_4d<signal_type> signal_it)
//{
//    sc_map_iterator<signal_type> *sig_map_it = &signal_it;
//    bind(*sig_map_it);
//
//    return;
//}
//
////******************************************************************************
//template<typename sc_map_T>
//template <typename signal_type>
//void sc_map_iterator<object_type>::operator() (sc_map_iter_4d<signal_type>
//        signal_it)
//{
//    bind(signal_it);
//
//    return;
//}

//******************************************************************************
template<typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(base_map_type& sc_map,
        size_type vect_pos) :
        sc_map(&sc_map),
        vect_pos(vect_pos)
{}

//******************************************************************************
template<typename sc_map_T>
typename sc_map_iterator<sc_map_T>::size_type
        sc_map_iterator<sc_map_T>::get_vect_pos()
{
    return (vect_pos);
}

//******************************************************************************
template<typename sc_map_T>
void sc_map_iterator<sc_map_T>::set_vect_pos(size_type vect_pos)
{
    this->vect_pos = vect_pos;

    return;
}

//******************************************************************************
template<typename sc_map_T>
bool sc_map_iterator<sc_map_T>::update_dim(key_type& key,
        const key_type key_start, const key_type key_stop,
        const cnt_direction_t direction)
{
    if (direction == up)
    {
        ++key;
        if (key <= key_stop)
        {
            return true;
        }
        else
        {
            key = key_start;
            return false;
        }
    }
    else
    {
        --key;
        if (key >= key_stop)
        {
            return true;
        }
        else
        {
            key = key_start;
            return false;
        }
    }
};
