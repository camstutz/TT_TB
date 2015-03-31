/*!
 * @file prbf_element.cpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_element.hpp"

// *****************************************************************************
void prbf_element::set_type_field(prbf_element_type type_field)
{
    this->type_field = type_field;

    return;
}
// *****************************************************************************
prbf_element_type prbf_element::get_type_field() const
{
    return (type_field);
}
