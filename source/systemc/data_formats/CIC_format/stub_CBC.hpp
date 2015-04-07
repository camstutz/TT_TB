/*!
 * @file stub_CBC.hpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "stub_type.hpp"

#include <string>
#include <sstream>
#include <iomanip>

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
class stub_CBC : public CIC::stub_type
{
public:
    typedef unsigned int bunch_crossing_t;
    typedef unsigned int fe_chip_ID_t;
    typedef unsigned int strip_t;
    typedef unsigned int bend_t;

    stub_CBC();
    stub_CBC(bunch_crossing_t, fe_chip_ID_t, strip_t, bend_t);

    void set_bunch_crossing(bunch_crossing_t bunch_crossing);
    bunch_crossing_t get_bunch_crossing() const;
    void set_fe_chip_ID(fe_chip_ID_t fe_chip_ID);
    fe_chip_ID_t get_fe_chip_ID() const;
    void set_strip(strip_t strip);
    strip_t get_strip() const;
    void set_bend(bend_t bend);
    bend_t get_bend() const;

    virtual std::string get_string() const;

protected:
    bunch_crossing_t bunch_crossing;
    fe_chip_ID_t fe_chip_ID;
    strip_t strip;
    bend_t bend;

    void set(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);

    std::string get_base_string() const;
};

// *****************************************************************************
} // namespace CIC
