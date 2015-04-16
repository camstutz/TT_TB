/*!
 * @file PRBF_frame.hpp
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

#include "header.hpp"
#include "trailer.hpp"
#include "stub_element.hpp"

#include "systemc.h"

#include <vector>
#include <sstream>
#include <string>

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************

template <typename stub_type>
class PRBF_frame;

template <typename stub_type>
void sc_trace (sc_trace_file* tf, const PRBF_frame<stub_type>& v, const std::string& name);

// *****************************************************************************
template <typename stub_type>
class PRBF_frame
{
public:
    typedef header header_t;
    typedef trailer trailer_t;
    typedef stub_type stub_t;
    typedef stub_element<stub_t> stub_element_t;
    typedef std::vector<stub_element_t> stub_vector_t;

    PRBF_frame();
    PRBF_frame(header::bunch_crossing_ID_t bunch_crossing);

    void set_bunch_crossing(header::bunch_crossing_ID_t bunch_crossing);
    header get_header() const;
    trailer get_trailer() const;

    void add_stub(stub_element_t stub);
    typename stub_vector_t::size_type stub_count() const;
    void reset_stub_ptr();
    bool get_stub(stub_element_t& stub);

    bool operator== (const PRBF_frame& rhs) const;
    PRBF_frame& operator= (const PRBF_frame& rhs);

    std::string get_string() const;

private:
    header header_element;
    stub_vector_t stub_vector;
    trailer trailer_element;

    typename stub_vector_t::iterator stub_it;

friend void sc_trace <> (sc_trace_file* tf, const PRBF_frame& v, const std::string& name);

};

template <typename stub_type>
std::ostream& operator<< (std::ostream& stream, const PRBF_frame<stub_type>& frame);

// *****************************************************************************

// *****************************************************************************
template <typename stub_type>
PRBF_frame<stub_type>::PRBF_frame()
{
    reset_stub_ptr();

    return;
}

// *****************************************************************************
template <typename stub_type>
PRBF_frame<stub_type>::PRBF_frame(header::bunch_crossing_ID_t bunch_crossing) :
    header_element(bunch_crossing)
{
    reset_stub_ptr();

    return;
}

// *****************************************************************************
template <typename stub_type>
void PRBF_frame<stub_type>::set_bunch_crossing(header::bunch_crossing_ID_t
        bunch_crossing)
{
    header_element.set_bunch_crossing_ID(bunch_crossing);

    return;
}

// *****************************************************************************
template <typename stub_type>
header PRBF_frame<stub_type>::get_header() const
{
    return header_element;
}

// *****************************************************************************
template <typename stub_type>
trailer PRBF_frame<stub_type>::get_trailer() const
{
    return trailer_element;
}

// *****************************************************************************
template <typename stub_type>
void PRBF_frame<stub_type>::add_stub(stub_element_t stub)
{
    stub_vector.push_back(stub);
    trailer_element.set_stub_count(stub_vector.size());

    return;
}

// *****************************************************************************
template <typename stub_type>
typename PRBF_frame<stub_type>::stub_vector_t::size_type
        PRBF_frame<stub_type>::stub_count() const
{
    return stub_vector.size();
}

// *****************************************************************************
template <typename stub_type>
void PRBF_frame<stub_type>::reset_stub_ptr()
{
    stub_it = stub_vector.begin();

    return;
}

// *****************************************************************************
template <typename stub_type>
bool PRBF_frame<stub_type>::get_stub(stub_element_t& stub)
{
    bool valid = false;

    if (stub_it != stub_vector.end())
    {
        stub = *stub_it;
        ++stub_it;

        valid = true;
    }
    else
    {
        valid = false;
    }

    return valid;
}

// *****************************************************************************
template <typename stub_type>
bool PRBF_frame<stub_type>::operator== (const PRBF_frame& rhs) const
{
    bool equal = true;

    equal &= (rhs.header_element == header_element);
    equal &= (rhs.trailer_element == trailer_element);

    // tests for equal length, as the length is part of the header
    if (equal)
    {
        equal &= std::equal(stub_vector.begin(), stub_vector.end(), rhs.stub_vector.begin());
    }

    return equal;
}

// *****************************************************************************
template <typename stub_type>
typename PRBF_frame<stub_type>::PRBF_frame&
        PRBF_frame<stub_type>::operator= (const PRBF_frame& rhs)
{
    header_element = rhs.header_element;
    trailer_element = rhs.trailer_element;

    stub_vector = rhs.stub_vector;

    return *this;
}

// *****************************************************************************
template <typename stub_type>
std::string PRBF_frame<stub_type>::get_string() const
{
    std::stringstream out_string;

    out_string << header_element.get_string() << std::endl;
    typename stub_vector_t::const_iterator local_stub_it = stub_vector.begin();
    for(; local_stub_it != stub_vector.end(); ++local_stub_it)
    {
        out_string << local_stub_it->get_string() << std::endl;
    }
    out_string << trailer_element.get_string();

    return out_string.str();
}

// *****************************************************************************
template <typename stub_type>
void sc_trace (sc_trace_file* tf, const PRBF_frame<stub_type>& v,
        const std::string& name)
{
    std::cerr << "No implementation of PRBF_frame.sc_trace()" << std::endl;

    return;
}

// *****************************************************************************
template <typename stub_type>
std::ostream& operator<< (std::ostream& stream, const PRBF_frame<stub_type>&
        frame)
{
    stream << frame.get_string();

    return stream;
}

// *****************************************************************************
} // namespace PRBF
