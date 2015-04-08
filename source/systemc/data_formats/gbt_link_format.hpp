/*!
 * @file gbt_link_format.hpp
 * @author Christian Amstutz
 * @date April 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include <string>
#include <sstream>
#include <iostream>

// *****************************************************************************
template <typename FRAME_TYPE>
class gbt_link_format;

template <typename FRAME_TYPE>
ostream& operator<< (ostream &os, gbt_link_format<FRAME_TYPE> const &v);

template <typename FRAME_TYPE>
void sc_trace (sc_trace_file* tf, const gbt_link_format<FRAME_TYPE>& v,
            const std::string& name);

// *****************************************************************************
template <typename FRAME_TYPE>
class gbt_link_format
{
public:
    typedef FRAME_TYPE frame_t;

    gbt_link_format();
    gbt_link_format(const frame_t left, const frame_t right);

    void set_left(const frame_t frame);
    frame_t get_left() const;
    void set_right(const frame_t frame);
    frame_t get_right() const;

    /** Comparison of two gbt_link_format objects */
    bool operator== (const gbt_link_format& rhs) const;

    /** Assignment operator for gbt_link_format */
    gbt_link_format& operator= (const gbt_link_format& rhs);

public:
    frame_t frame_packet[2];

friend ostream& operator<< <> (ostream &os, gbt_link_format const &v);

/** Function for tracing support in SystemC */
friend void sc_trace <> (sc_trace_file* tf, const gbt_link_format& v,
            const std::string& name);
};

// *****************************************************************************

// *****************************************************************************
template <typename FRAME_TYPE>
gbt_link_format<FRAME_TYPE>::gbt_link_format()
{
    frame_packet[0] = frame_t();
    frame_packet[1] = frame_t();

    return;
}

// *****************************************************************************
template <typename FRAME_TYPE>
gbt_link_format<FRAME_TYPE>::gbt_link_format(const frame_t left,
        const frame_t right)
{
    frame_packet[0] = left;
    frame_packet[1] = right;

    return;
}

// *****************************************************************************
template <typename FRAME_TYPE>
void gbt_link_format<FRAME_TYPE>::set_left(const frame_t frame)
{
    frame_packet[0] = frame;

    return;
}

// *****************************************************************************
template <typename FRAME_TYPE>
typename gbt_link_format<FRAME_TYPE>::frame_t gbt_link_format<FRAME_TYPE>::get_left() const
{
    return (frame_packet[0]);
}

// *****************************************************************************
template <typename FRAME_TYPE>
void gbt_link_format<FRAME_TYPE>::set_right(const frame_t frame)
{
    frame_packet[1] = frame;

    return;
}

// *****************************************************************************
template <typename FRAME_TYPE>
typename gbt_link_format<FRAME_TYPE>::frame_t gbt_link_format<FRAME_TYPE>::get_right() const
{
    return (frame_packet[1]);
}

// *****************************************************************************
template <typename FRAME_TYPE>
bool gbt_link_format<FRAME_TYPE>::operator== (const gbt_link_format& rhs) const
{
    bool equal = true;

    equal &= (frame_packet[0] == rhs.frame_packet[0]);
    equal &= (frame_packet[1] == rhs.frame_packet[1]);

    return (equal);
}

// *****************************************************************************
template <typename FRAME_TYPE>
typename gbt_link_format<FRAME_TYPE>::gbt_link_format&
        gbt_link_format<FRAME_TYPE>::operator= (const gbt_link_format& rhs)
{
    frame_packet[0] = rhs.frame_packet[0];
    frame_packet[1] = rhs.frame_packet[1];

    return (*this);
}

// *****************************************************************************
template <typename FRAME_TYPE>
ostream& operator<< (ostream &os, gbt_link_format<FRAME_TYPE> const &v)
{
    os << "Left:" << std::endl;
    os << v.frame_packet[0] << std::endl;
    os << "Right:" << std::endl;
    os << v.frame_packet[1] << std::endl;

    return (os);
}

// *****************************************************************************
template <typename FRAME_TYPE>
void sc_trace (sc_trace_file* tf, const gbt_link_format<FRAME_TYPE>& v,
        const std::string& name)
{
    std::cerr << "No implementation of gbt_link_formar.sc_trace()" << std::endl;

    return;
}
