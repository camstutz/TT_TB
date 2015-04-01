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

#include "element_type.hpp"

using namespace PRBF;

// *****************************************************************************
namespace PRBF {

class frame_element
{
public:
    element_type type_field;

    void set_type_field(element_type type_field);
    element_type get_type_field() const;
};

} // namespace PRBF
