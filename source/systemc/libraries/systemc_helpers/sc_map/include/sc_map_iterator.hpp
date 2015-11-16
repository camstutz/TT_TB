/*!
 * @file sc_map_iterator.hpp
 * @author Christian Amstutz
 * @date July 15, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map_range.hpp"

#include <systemc.h>

#include <iterator>
#include <utility>


template <typename range_T, typename object_T>
class sc_map_base;

//******************************************************************************
template <typename sc_map_T>
class sc_map_iterator : public std::iterator<std::forward_iterator_tag, typename sc_map_T::object_type>
{
public:
    typedef sc_map_T map_type;
    typedef typename map_type::object_type object_type;
    typedef typename map_type::key_type key_type;

    typedef bool end_type;

    static const end_type end;

public:
    sc_map_iterator(sc_map_T* sc_map);
    sc_map_iterator(sc_map_T* sc_map, const end_type end_id);
    sc_map_iterator(sc_map_T* sc_map, const key_type& map_pos);
    sc_map_iterator(sc_map_T* sc_map, const sc_map_range<key_type>& range);
    sc_map_iterator(sc_map_T* sc_map, const sc_map_range<key_type>& range, const key_type& map_pos);
    sc_map_iterator(sc_map_T* sc_map, const key_type& start_key, const key_type& end_key);
    sc_map_iterator(const sc_map_iterator& original);
    virtual ~sc_map_iterator();

    sc_map_iterator& operator= (const sc_map_iterator& rhs);

    bool operator==(const sc_map_iterator& other) const;
    bool operator!=(const sc_map_iterator& other) const;

    virtual sc_map_iterator& operator++();
    virtual object_type& operator*();
    virtual object_type* operator->();

    template<typename data_type>
    void write(const data_type& value);
    template<typename data_type>
    void operator= (const data_type& value);

    template <typename signal_T>
    void bind(sc_signal<signal_T>& signal);
    template <typename signal_T>
    void operator() (sc_signal<signal_T>& signal);
    template <typename signal_range_T, typename signal_T>
    void bind(sc_map_base<signal_range_T, signal_T>& signal_map);
    template <typename signal_range_T, typename signal_T>
    void operator() (sc_map_base<signal_range_T, signal_T>& signal_map);
    template <typename signal_map_T>
    void bind(sc_map_iterator<signal_map_T> signal_it);
    template <typename signal_map_T>
    void operator() (sc_map_iterator<signal_map_T> signal_it);

    std::pair<end_type, key_type> get_key() const;

private:
    map_type* map;
    sc_map_range<key_type>* range;
    key_type position;
    end_type end_flag;
};

//******************************************************************************

//******************************************************************************
template <typename sc_map_T>
const typename sc_map_iterator<sc_map_T>::end_type
        sc_map_iterator<sc_map_T>::end = true;

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(sc_map_T* sc_map) :
        map(sc_map),
        end_flag(!end)
{
    range = map->get_range()->clone();
    position = range->first();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const end_type end_id) :
        map(sc_map),
        end_flag(end_id)
{
    range = map->get_range()->clone();
    position = range->first();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const key_type& map_pos) :
        map(sc_map),
        position(map_pos),
        end_flag(!end)
{
    range = map->get_range()->clone();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const sc_map_range<key_type>& range) :
        map(sc_map),
        end_flag(!end)
{
    this->range = range.clone();

    position = this->range->first();

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const sc_map_range<key_type>& range, const key_type& map_pos) :
        map(sc_map),
        end_flag(!end)
{
    this->range = range.clone();

    position = map_pos;

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(map_type* sc_map,
        const key_type& start_key, const key_type& end_key) :
        map(sc_map),
        position(start_key),
        end_flag(!end)
{
    range = new typename map_type::range_type(map->get_range(), start_key, end_key);

    return;
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::sc_map_iterator(const sc_map_iterator& original)
{
    map = original.map;
    typename map_type::range_type* original_range_ptr = static_cast<typename map_type::range_type*>(original.range);
    range = new typename map_type::range_type(*original_range_ptr);
    position = original.position;
    end_flag = original.end_flag;

    return;
}

//************************************************************ ******************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>::~sc_map_iterator()
{
    delete range;

    return;
};

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>& sc_map_iterator<sc_map_T>::operator= (const sc_map_iterator& rhs)
{
    map = rhs.map;
    *range = *(rhs.range);
    position = rhs.position;
    end_flag = rhs.end_flag;

    return *this;
}

//******************************************************************************
template <typename sc_map_T>
bool sc_map_iterator<sc_map_T>::operator==(const sc_map_iterator& rhs)
        const
{
    bool equal = false;

    if (this->end_flag == rhs.end_flag)
    {
        if (this->end_flag == end)
        {
            equal = true;
        }
        else
        {
            equal &= this->map == rhs.map;
            equal &= this->position == rhs.position;
        }
    }

    return equal;
}

//******************************************************************************
template <typename sc_map_T>
bool sc_map_iterator<sc_map_T>::operator!=(const sc_map_iterator& other) const
{
    return !(*this==other);
}

//******************************************************************************
template <typename sc_map_T>
sc_map_iterator<sc_map_T>& sc_map_iterator<sc_map_T>::operator++ ()
{
    bool success = range->next_key(position);
    if (!success)
    {
        end_flag = true;
    }

    return *this;
}

//******************************************************************************
template <typename sc_map_T>
typename sc_map_iterator<sc_map_T>::object_type&
        sc_map_iterator<sc_map_T>::operator*()
{
    // todo: ensure that out of range is not accessed (end iterator)
    return *(map->objects[position]);
}

//******************************************************************************
template <typename sc_map_T>
typename sc_map_iterator<sc_map_T>::object_type*
        sc_map_iterator<sc_map_T>::operator->()
{
    return map->objects[position];
}

//******************************************************************************
template <typename sc_map_T>
template <typename data_type>
void sc_map_iterator<sc_map_T>::write(const data_type& value)
{
    for (; *this != map->end(); ++(*this))
    {
        (**this).write(value);
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename data_type>
void sc_map_iterator<sc_map_T>::operator= (const data_type& value)
{
    write(value);

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_T>
void sc_map_iterator<sc_map_T>::bind(sc_signal<signal_T>& signal)
{
    for (; *this != map->end(); ++(*this))
    {
        (**this).bind(signal);
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_T>
void sc_map_iterator<sc_map_T>::operator() (sc_signal<signal_T>& signal)
{
    bind(signal);

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_range_T, typename signal_T>
void sc_map_iterator<sc_map_T>::bind(
        sc_map_base<signal_range_T, signal_T>& signal_map)
{
    for (typename sc_map_base<signal_range_T, signal_T>::iterator signal_it = signal_map.begin();
         *this != map->end();
         ++(*this))
    {
        (**this).bind(*signal_it);

        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_range_T, typename signal_T>
void sc_map_iterator<sc_map_T>::operator() (
        sc_map_base<signal_range_T, signal_T>& signal_map)
{
    bind(signal_map);

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_map_T>
void sc_map_iterator<sc_map_T>::bind(sc_map_iterator<signal_map_T> signal_it)
{
    for (; *this != map->end(); ++(*this))
    {
        (**this).bind(*signal_it);

        ++signal_it;
    }

    return;
}

//******************************************************************************
template <typename sc_map_T>
template <typename signal_map_T>
void sc_map_iterator<sc_map_T>::operator() (
        sc_map_iterator<signal_map_T> signal_it)
{
    bind(signal_it);

    return;
}

//******************************************************************************
template <typename sc_map_T>
std::pair<typename sc_map_iterator<sc_map_T>::end_type,
        typename sc_map_iterator<sc_map_T>::key_type>
        sc_map_iterator<sc_map_T>::get_key() const
{
    return std::pair<end_type, key_type>(end_flag, position);
}

////******************************************************************************
//template <typename sc_map_T>
//bool sc_map_iterator<sc_map_T>::update_dim(key_type& key,
//        const key_type key_start, const key_type key_stop,
//        const cnt_direction_t direction)
//{
//    if (direction == up)
//    {
//        ++key;
//        if (key <= key_stop)
//        {
//            return true;
//        }
//        else
//        {
//            key = key_start;
//            return false;
//        }
//    }
//    else
//    {
//        --key;
//        if (key >= key_stop)
//        {
//            return true;
//        }
//        else
//        {
//            key = key_start;
//            return false;
//        }
//    }
//};
