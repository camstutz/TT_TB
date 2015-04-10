/*!
 * @file frame_element.hpp
 * @author Christian Amstutz
 * @date April 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "element_type.hpp"

#include "systemc.h"

#include <string>
#include <sstream>

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************

template <typename payload_type>
class frame_element;

template <typename payload_type>
void sc_trace (sc_trace_file* tf, const frame_element<payload_type>& v, const std::string& name);

// *****************************************************************************
template <typename payload_type>
class frame_element
{
public:
    typedef payload_type payload_t;

    void set_type_field(element_type type_field);
    element_type get_type_field() const;

    bool operator== (const frame_element& rhs) const;
    frame_element& operator= (const frame_element& rhs);

    std::string get_string() const;

protected:
    element_type type_field;
    payload_t payload;

friend void sc_trace <> (sc_trace_file* tf, const frame_element& v, const std::string& name);

};

template <typename payload_type>
std::ostream& operator<< (std::ostream& stream, const frame_element<payload_type>& element);

// *****************************************************************************

// *****************************************************************************
template <typename payload_type>
void frame_element<payload_type>::set_type_field(element_type type_field)
{
    this->type_field = type_field;

    return;
}

// *****************************************************************************
template <typename payload_type>
element_type frame_element<payload_type>::get_type_field() const
{
    return (type_field);
}

// *****************************************************************************
template <typename payload_type>
bool frame_element<payload_type>::operator== (const frame_element& rhs) const
{
    bool equal = true;

    equal &= (rhs.type_field == type_field);
    equal &= (rhs.payload == payload);

    return equal;
}

// *****************************************************************************
template <typename payload_type>
typename frame_element<payload_type>::frame_element&
        frame_element<payload_type>::operator= (const frame_element& rhs)
{
    type_field = rhs.type_field;
    payload = rhs.payload;

    return *this;
}

// *****************************************************************************
template <typename payload_type>
std::string frame_element<payload_type>::get_string() const
{
    std::stringstream out_string;

    out_string << "[";
    out_string << get_type_field().get_string();
    out_string << "-";
    out_string << std::hex << std::showbase <<  payload;
    out_string << "]";

    return out_string.str();
}

// *****************************************************************************
template <typename payload_type>
void sc_trace (sc_trace_file* tf, const frame_element<payload_type>& v,
        const std::string& name)
{
    std::cerr << "No implementation of frame_element.sc_trace()" << std::endl;

    return;
}

// *****************************************************************************
template <typename payload_type>
std::ostream& operator<< (std::ostream& stream, const
        frame_element<payload_type>& element)
{
    stream << element.get_string();

    return stream;
}

// *****************************************************************************
} // namespace PRBF
