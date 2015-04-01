/*!
 * @file trailer.hpp
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

#include <iostream>

#include "frame_element.hpp"

// *****************************************************************************
namespace PRBF
{

class trailer : public frame_element
{
public:
    typedef unsigned int stub_count_t;

    trailer();

    void set_type_field(element_type type_field);
    void set_stub_count(stub_count_t stub_count);
    stub_count_t get_stub_count() const;

private:
    stub_count_t stub_count;
};

} // namespace PRBF
