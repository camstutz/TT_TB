/*!
 * @file fm_out_data.cpp
 * @author Christian Amstutz
 * @date April 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "gbt_link_format.hpp"

// *****************************************************************************
gbt_link_format::gbt_link_format()
{
    frame_packet[0] = frame_t();
    frame_packet[1] = frame_t();

    return;
}

// *****************************************************************************
gbt_link_format::gbt_link_format(const frame_t left,
        const frame_t right)
{
    frame_packet[0] = left;
    frame_packet[1] = right;

    return;
}

// *****************************************************************************
void gbt_link_format::set_left(const frame_t frame)
{
    frame_packet[0] = frame;

    return;
}

// *****************************************************************************
typename gbt_link_format::frame_t gbt_link_format::get_left() const
{
    return (frame_packet[0]);
}

// *****************************************************************************
void gbt_link_format::set_right(const frame_t frame)
{
    frame_packet[1] = frame;

    return;
}

// *****************************************************************************
typename gbt_link_format::frame_t gbt_link_format::get_right() const
{
    return (frame_packet[1]);
}

// *****************************************************************************
bool gbt_link_format::operator== (const gbt_link_format& rhs) const
{
    bool equal = true;

    equal &= (frame_packet[0] == rhs.frame_packet[0]);
    equal &= (frame_packet[1] == rhs.frame_packet[1]);

    return (equal);
}

// *****************************************************************************
typename gbt_link_format::gbt_link_format&
        gbt_link_format::operator= (const gbt_link_format& rhs)
{
    frame_packet[0] = rhs.frame_packet[0];
    frame_packet[1] = rhs.frame_packet[1];

    return *this;
}

// *****************************************************************************
ostream& operator<< (ostream &os, gbt_link_format const &v)
{
    os << "Left:" << std::endl;
    os << v.frame_packet[0] << std::endl;
    os << "Right:" << std::endl;
    os << v.frame_packet[1] << std::endl;

    return os;
}

// *****************************************************************************
void sc_trace (sc_trace_file* tf, const gbt_link_format& v,
        const std::string& name)
{
    std::cerr << "No implementation of gbt_link_formar.sc_trace()" << std::endl;

    return;
}
