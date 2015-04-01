/*!
 * @file stub_element.cpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_element.hpp"

using namespace PRBF;

// *****************************************************************************
stub_element::stub_element()
{
    set_type_field(element_type(element_type::local, 0, element_type::MPA));

    return;
}
