/*!
 * @file prbf_element.hpp
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

#include "prbf_element_type.hpp"

// *****************************************************************************
class prbf_element
{
public:
    prbf_element_type type_field;

    void set_type_field(prbf_element_type type_field);
    prbf_element_type get_type_field() const;
};
