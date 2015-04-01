/*!
 * @file PRBF_frame.hpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>

#include "header.hpp"
#include "trailer.hpp"
#include "stub_element.hpp"

using namespace PRBF;

// *****************************************************************************
template <typename stub_type>
class PRBF_frame
{
public:
    typedef stub_type stub_t;

    PRBF_frame(header::bunch_crossing_ID_t bunch_crossing);

    void set_bunch_crossing(header::bunch_crossing_ID_t bunch_crossing);
    header get_header() const;
    trailer get_trailer() const;

    void add_stub(stub_t stub);

private:
    header header_element;
    std::vector<stub_t> stub_vector;
    trailer trailer_element;
};

// *****************************************************************************

// *****************************************************************************
template <typename stub_type>
PRBF_frame<stub_type>::PRBF_frame(header::bunch_crossing_ID_t bunch_crossing) :
    header_element(bunch_crossing)
{
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
    return (header_element);
}

// *****************************************************************************
template <typename stub_type>
trailer PRBF_frame<stub_type>::get_trailer() const
{
    return (trailer_element);
}

// *****************************************************************************
template <typename stub_type>
void PRBF_frame<stub_type>::add_stub(stub_t stub)
{
    stub_vector.push_back(stub);
    trailer_element.set_stub_count(stub_vector.size());

    return;
}
