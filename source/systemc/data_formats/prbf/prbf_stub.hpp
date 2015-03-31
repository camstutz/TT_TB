/*!
 * @file prbf_stub.hpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "prbf_element.hpp"

// *****************************************************************************
template <class stub_type>
class prbf_stub : public prbf_element
{
public:
    typedef stub_type stub_t;

    prbf_stub();

private:
    stub_t stub;
};


// *****************************************************************************
template <class stub_type>
prbf_stub<stub_type>::prbf_stub()
{
    set_type_field(prbf_element_type(prbf_element_type::local, 0, prbf_element_type::MPA));

    // TODO: change stub initialization
    stub = 0;

    return;
}
