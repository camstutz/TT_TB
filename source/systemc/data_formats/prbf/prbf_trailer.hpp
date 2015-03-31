/*!
 * @file prbf_trailer.hpp
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
class prbf_trailer : public prbf_element
{
public:
    typedef unsigned int stub_count_t;

    void set_stub_count(stub_count_t stub_count);
    stub_count_t get_stub_count() const;

private:
    stub_count_t stub_count;
};
