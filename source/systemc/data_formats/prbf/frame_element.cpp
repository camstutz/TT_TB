/*!
 * @file frame_element.cpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "frame_element.hpp"

using namespace PRBF;

// *****************************************************************************
void frame_element::set_type_field(element_type type_field)
{
    this->type_field = type_field;

    return;
}

// *****************************************************************************
element_type frame_element::get_type_field() const
{
    return (type_field);
}
