/*!
 * @file gbt_link_format.hpp
 * @author Christian Amstutz
 * @date April 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "CIC_format/CIC_format.hpp"

#include <systemc.h>

#include <string>
#include <sstream>
#include <iostream>

// *****************************************************************************
class gbt_link_format
{
public:
    typedef CIC_frame frame_t;

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

friend ostream& operator<< (ostream &os, gbt_link_format const &v);

friend void sc_trace(sc_trace_file* tf, const gbt_link_format& v,
            const std::string& name);
};
