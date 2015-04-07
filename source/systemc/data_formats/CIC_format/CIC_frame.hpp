/*!
 * @file CIC_frame.hpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <sstream>
#include <string>

#include "header.hpp"
#include "trailer.hpp"

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
template <typename stub_type>
class CIC_frame
{
public:
    typedef stub_type stub_t;
    typedef std::vector<stub_t> stub_vector_t;

    CIC_frame();

    void set_header(CIC::header new_header);
    CIC::header get_header() const;
    CIC::trailer get_trailer() const;

    void add_stub(stub_t stub);
    typename stub_vector_t::size_type stub_count() const;
    void reset_stub_ptr();
    bool get_stub(stub_t *stub) const;

    std::string get_string() const;

private:
    CIC::header header_element;
    stub_vector_t stub_vector;
    CIC::trailer trailer_element;

    typename stub_vector_t::iterator stub_it;
};

template <typename stub_type>
std::ostream& operator<< (std::ostream& stream, const CIC_frame<stub_type>&
        frame);

// *****************************************************************************

// *****************************************************************************
template <typename stub_type>
CIC_frame<stub_type>::CIC_frame()
{
    header_element = CIC::header();
    reset_stub_ptr();
    trailer_element = CIC::trailer();

    return;
}

// *****************************************************************************
template <typename stub_type>
CIC::header CIC_frame<stub_type>::get_header() const
{
    return (header_element);
}

// *****************************************************************************
template <typename stub_type>
CIC::trailer CIC_frame<stub_type>::get_trailer() const
{
    return (trailer_element);
}

// *****************************************************************************
template <typename stub_type>
void CIC_frame<stub_type>::add_stub(stub_t stub)
{
    stub_vector.push_back(stub);
    header_element.set_stub_count(stub_count());

    return;
}

// *****************************************************************************
template <typename stub_type>
typename CIC_frame<stub_type>::stub_vector_t::size_type
        CIC_frame<stub_type>::stub_count() const
{
    return (stub_vector.size());
}

// *****************************************************************************
template <typename stub_type>
void CIC_frame<stub_type>::reset_stub_ptr()
{
    stub_it = stub_vector.begin();

    return;
}

// *****************************************************************************
template <typename stub_type>
bool CIC_frame<stub_type>::get_stub(stub_t *stub) const
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
        stub = NULL;

        valid = false;
    }

    return (valid);
}

// *****************************************************************************
template <typename stub_type>
std::string CIC_frame<stub_type>::get_string() const
{
    std::stringstream out_string;

    out_string << header_element << std::endl;
    typename stub_vector_t::const_iterator local_stub_it = stub_vector.begin();
    for(; local_stub_it != stub_vector.end(); ++local_stub_it)
    {
        out_string << local_stub_it->get_string() << std::endl;
    }
    out_string << trailer_element;

    return (out_string.str());
}

// *****************************************************************************
template <typename stub_type>
std::ostream& operator<< (std::ostream& stream, const CIC_frame<stub_type>&
        frame)
{
    stream << frame.get_string();

    return (stream);
}

// *****************************************************************************
} // namespace CIC
