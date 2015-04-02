/*!
 * @file header.hpp
 * @author Christian Amstutz
 * @date April 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <iomanip>

// *****************************************************************************
namespace CIC
{

class header
{
public:
    typedef enum
    {
        CBC = 0x0,
        MPA = 0x1
    } fe_type_t;
    typedef unsigned int hw_status_t;
    typedef unsigned int bunch_crossing_t;
    typedef unsigned int stub_count_t;

    header();

    void set(fe_type_t fe_type, hw_status_t hw_status, bunch_crossing_t bunch_crossing);
    void set_fe_type(fe_type_t fe_type);
    fe_type_t get_fe_type() const;
    void set_hw_status(hw_status_t hw_status);
    hw_status_t get_hw_status() const;
    void set_bunch_crossing(bunch_crossing_t bunch_crossing);
    bunch_crossing_t get_bunch_crossing() const;
    stub_count_t get_stub_count() const;

    std::string get_string();

private:
    fe_type_t fe_type;
    hw_status_t hw_status;
    bunch_crossing_t bunch_crossing;
    stub_count_t stub_count;

    void set_stub_count(stub_count_t stub_count);
};

} // namespace CIC
