/*!
 * @file CIC_frame.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../stub/stub.hpp"

#include "systemc.h"

#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include "../CIC_frame/header.hpp"
#include "../CIC_frame/trailer.hpp"

// *****************************************************************************
using namespace CIC;

// *****************************************************************************
class CIC_frame
{
public:
    typedef CIC::header header_t;
    typedef CIC::trailer trailer_t;
    typedef std::vector<stub> stub_vector_t;

    stub_config stub_configuration;

    CIC_frame();
    CIC_frame(stub_config stub_configuration);

    void set_header(header_t new_header);
    header_t get_header() const;
    trailer_t get_trailer() const;

    bool is_CBC_frame() const;
    bool is_MPA_frame() const;
    bool add_stub(stub new_stub);
    typename stub_vector_t::size_type stub_count() const;
    void reset_stub_ptr();
    bool get_stub(stub& return_stub);

    bool operator== (const CIC_frame& rhs) const;
    CIC_frame& operator= (const CIC_frame& rhs);

    std::string get_string() const;

private:
    header_t header_element;
    stub_vector_t stub_vector;
    trailer_t trailer_element;

    stub_vector_t::iterator stub_it;

    void init();

    friend void sc_trace(sc_trace_file* tf, const CIC_frame& v, const std::string& name);
};

std::ostream& operator<< (std::ostream& stream, const CIC_frame& frame);
