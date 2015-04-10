/*!
 * @file CIC_frame.hpp
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
#include "stub_CBC.hpp"
#include "stub_MPA.hpp"

#include "systemc.h"

#include "boost/variant.hpp"

#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

// *****************************************************************************
using namespace CIC;

// *****************************************************************************
class CIC_frame
{
public:
    typedef header header_t;
    typedef trailer trailer_t;
    typedef boost::variant<stub_CBC, stub_MPA> stub_t;
    typedef std::vector<stub_t> stub_vector_t;

    CIC_frame();

    void set_header(header_t new_header);
    header_t get_header() const;
    trailer_t get_trailer() const;

    bool is_CBC_frame() const;
    bool is_MPA_frame() const;
    bool add_stub(stub_CBC stub);
    bool add_stub(stub_MPA stub);
    typename stub_vector_t::size_type stub_count() const;
    void reset_stub_ptr();
    bool get_stub(stub_CBC& stub);
    bool get_stub(stub_MPA& stub);

    bool operator== (const CIC_frame& rhs) const;
    CIC_frame& operator= (const CIC_frame& rhs);

    std::string get_string() const;

private:
    header_t header_element;
    stub_vector_t stub_vector;
    trailer_t trailer_element;

    stub_vector_t::iterator stub_it;

friend void sc_trace(sc_trace_file* tf, const CIC_frame& v, const std::string& name);
};

std::ostream& operator<< (std::ostream& stream, const CIC_frame& frame);
