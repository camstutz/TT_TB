/*!
 * @file stub_element.hpp
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

#include "frame_element.hpp"

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************
template <typename stub_type>
class stub_element : public frame_element<stub_type>
{
public:
    typedef stub_type stub_t;

    stub_element();
    stub_element(element_type type_field, stub_t stub);

    void set_stub(stub_t stub);
    stub_t get_stub() const;
};

// *****************************************************************************

// *****************************************************************************
template <typename stub_type>
stub_element<stub_type>::stub_element()
{
    this->set_type_field(element_type(element_type::local, 0, element_type::MPA));

    return;
}

// *****************************************************************************
template <typename stub_type>
stub_element<stub_type>::stub_element(element_type type_field, stub_t stub)
{
    this->set_type_field(type_field);
    set_stub(stub);

    return;
}

// *****************************************************************************
template <typename stub_type>
void stub_element<stub_type>::set_stub(stub_t stub)
{
    this->payload = stub;

    return;
}

// *****************************************************************************
template <typename stub_type>
typename stub_element<stub_type>::stub_t stub_element<stub_type>::get_stub() const
{
    return (this->payload);
}

// *****************************************************************************
} // namespace PRBF
