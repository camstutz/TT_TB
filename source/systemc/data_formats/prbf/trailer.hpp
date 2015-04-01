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
#include "element_type.hpp"

using namespace PRBF;

// *****************************************************************************
namespace PRBF
{

typedef unsigned int stub_count_type;

class trailer : public frame_element<stub_count_type>
{
public:
    typedef stub_count_type stub_count_t;

    trailer();

    void set_type_field(element_type type_field);
    void set_stub_count(stub_count_t stub_count);
    stub_count_t get_stub_count() const;

private:
};

} // namespace PRBF
