/*!
 * @file frame_element.hpp
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

#include <string>
#include <sstream>

#include "element_type.hpp"

using namespace PRBF;

// *****************************************************************************
namespace PRBF {

template <typename payload_type>
class frame_element
{
public:
    typedef payload_type payload_t;

    void set_type_field(element_type type_field);
    element_type get_type_field() const;

    std::string get_string() const;

protected:
    element_type type_field;
    payload_t payload;
};

} // namespace PRBF

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
std::string frame_element<payload_type>::get_string() const
{
    std::stringstream out_string;

    out_string << "[";
    out_string << get_type_field().get_string();
    out_string << payload;
    out_string << "]";

    return (out_string.str());
}
