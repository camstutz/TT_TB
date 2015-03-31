/*!
 * @file prbf_header.hpp
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

#include "prbf_element.hpp"

// *****************************************************************************
class prbf_header : public prbf_element
{
public:
    typedef unsigned int bunch_crossing_ID_t;

    prbf_header();

    void set_bunch_crossing_ID(bunch_crossing_ID_t bunch_crossing);
    bunch_crossing_ID_t get_bunch_crossing_ID() const;

private:
    bunch_crossing_ID_t bunch_crossing_ID;
};
