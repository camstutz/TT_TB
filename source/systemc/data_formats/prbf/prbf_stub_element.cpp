/*!
 * @file prbf_stub_element.cpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_stub_element.hpp"

// *****************************************************************************
prbf_stub_element::prbf_stub_element()
{
    set_type_field(prbf_element_type(prbf_element_type::local, 0, prbf_element_type::MPA));

    return;
}
