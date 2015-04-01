/*!
 * @file header.hpp
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

#include <iostream>

#include "frame_element.hpp"
#include "element_type.hpp"

using namespace PRBF;

// *****************************************************************************
namespace PRBF
{

typedef unsigned int bunch_crossing_ID_type;

class header : public frame_element<bunch_crossing_ID_type>
{
public:
    typedef bunch_crossing_ID_type bunch_crossing_ID_t;

    header();
    header(bunch_crossing_ID_t bunch_crossing);

    void set_type_field(element_type type_field);
    void set_bunch_crossing_ID(bunch_crossing_ID_t bunch_crossing);
    bunch_crossing_ID_t get_bunch_crossing_ID() const;

private:
};

} // namespace PRBF
