/*!
 * @file simple_stream_protocol.hpp
 * @author Christian Amstutz
 * @date November 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "stream_data_basetype.hpp"

// *****************************************************************************
template <typename value_type>
class simple_stream_protocol : public stream_data_basetype<value_type>
{
public:
    typedef typename stream_data_basetype<value_type>::opcode_t opcode_t;
    typedef typename stream_data_basetype<value_type>::value_t value_t;

    static const simple_stream_protocol<value_type> IDLE;
    static const simple_stream_protocol<value_type> START_WORD;

    simple_stream_protocol(const value_t& val = 0);
    simple_stream_protocol(const opcode_t& op, const value_t& val);
    simple_stream_protocol(const simple_stream_protocol<value_type> &copy_object);
};

// *****************************************************************************
template <typename value_type>
const simple_stream_protocol<value_type> simple_stream_protocol<value_type>::IDLE = simple_stream_protocol<value_type>(0xFF,0);

template <typename value_type>
const simple_stream_protocol<value_type> simple_stream_protocol<value_type>::START_WORD = simple_stream_protocol<value_type>(0xFE,0);

// *****************************************************************************
template <typename value_type>
simple_stream_protocol<value_type>::simple_stream_protocol(const value_t& val) :
        stream_data_basetype<value_type>(val)
{}

// *****************************************************************************
template <typename value_type>
simple_stream_protocol<value_type>::simple_stream_protocol(const opcode_t& op,
        const value_t& val) : stream_data_basetype<value_type>(op, val)
{}

// *****************************************************************************
template <typename value_type>
simple_stream_protocol<value_type>::simple_stream_protocol(
        const simple_stream_protocol<value_type> &copy_object)
{}
