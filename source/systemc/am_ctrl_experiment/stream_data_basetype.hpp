/*!
 * @file stream_data_basetype.hpp
 * @author Christian Amstutz
 * @date November 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <ostream>
#include <systemc.h>

template <typename value_type>
class stream_data_basetype
{
public:
    typedef unsigned int opcode_t;
    typedef value_type value_t;

    static const opcode_t NO_OPCODE = 0;

    stream_data_basetype(const stream_data_basetype &copy_object);
    stream_data_basetype(const value_t &val = 0);
    stream_data_basetype(const opcode_t &op, const value_t &val);

    bool is_opcode() const;

    stream_data_basetype& operator= (const stream_data_basetype& new_value);
    stream_data_basetype& operator= (const value_t& new_value);

    bool operator== (const stream_data_basetype& rhs) const;
    bool operator== (const value_t& rhs) const;

private:
    opcode_t opcode;
    value_t value;


    template <typename v_type>
    friend ostream& operator<< (ostream& os, stream_data_basetype<v_type> const& out_object);

    template <typename v_type>
    friend void sc_trace(sc_trace_file* tf, const stream_data_basetype<v_type>& tr_object, const std::string& NAME);
};

// *****************************************************************************
template <typename value_type>
stream_data_basetype<value_type>::stream_data_basetype(
        const stream_data_basetype &copy_object)
{
    opcode = copy_object.opcode;
    value = copy_object.value;

    return;
}

// *****************************************************************************
template <typename value_type>
stream_data_basetype<value_type>::stream_data_basetype(const value_t &val)
{
    opcode = NO_OPCODE;
    value = val;

    return;
}

// *****************************************************************************
template <typename value_type>
stream_data_basetype<value_type>::stream_data_basetype(const opcode_t &op,
        const value_t &val)
{
    opcode = op;
    value = val;

    return;
}

// *****************************************************************************
template <typename value_type>
bool stream_data_basetype<value_type>::is_opcode() const
{
    return (opcode != NO_OPCODE);
}

// *****************************************************************************
template <typename value_type>
stream_data_basetype<value_type>& stream_data_basetype<value_type>::operator= (
        const stream_data_basetype<value_type> &new_value)
{
    opcode = new_value.opcode;
    value  = new_value.value;

    return (*this);
}

// *****************************************************************************
template <typename value_type>
stream_data_basetype<value_type>& stream_data_basetype<value_type>::operator= (
        const value_t &new_value)
{
    opcode = NO_OPCODE;
    value = new_value;

    return (*this);
}

// *****************************************************************************
template <typename value_type>
bool stream_data_basetype<value_type>::operator== (
        const stream_data_basetype<value_type>& rhs) const
{
    return ((opcode == rhs.opcode) && (value == rhs.value));
}

// *****************************************************************************
template <typename value_type>
bool stream_data_basetype<value_type>::operator== (const value_t& rhs) const
{
    return ((opcode == NO_OPCODE) && (value == rhs));
}

// *****************************************************************************
template <typename value_type>
ostream& operator<< (ostream& os, stream_data_basetype<value_type> const&
        out_object)
{
    os << "(" << out_object.opcode << ":" << out_object.value << ")";

    return (os);
}

// *****************************************************************************
template <typename value_type>
void sc_trace(sc_trace_file* tf, const stream_data_basetype<value_type>&
        tr_object, const std::string& NAME)
{
    sc_trace(tf, tr_object.opcode, NAME + ".opcode");
    sc_trace(tf, tr_object.value, NAME + ".value");

    return;
}
