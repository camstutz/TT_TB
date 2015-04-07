/*!
 * @file stub_CBC.cpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_CBC.hpp"

using namespace CIC;

// *****************************************************************************
stub_CBC::stub_CBC()
{
    set(0, 0, 0, 0);

    return;
}

// *****************************************************************************
stub_CBC::stub_CBC(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chip_ID,
        strip_t strip, bend_t bend)
{
    set(bunch_crossing, fe_chip_ID, strip, bend);

    return;
}

// *****************************************************************************
stub_CBC::~stub_CBC()
{}

// *****************************************************************************
void stub_CBC::set(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chip_ID,
        strip_t strip, bend_t bend)
{
    set_bunch_crossing(bunch_crossing);
    set_fe_chip_ID(fe_chip_ID);
    set_strip(strip);
    set_bend(bend);

    return;
}

// *****************************************************************************
void stub_CBC::set_bunch_crossing(bunch_crossing_t bunch_crossing)
{
    this->bunch_crossing = bunch_crossing;

    return;
}

// *****************************************************************************
stub_CBC::bunch_crossing_t stub_CBC::get_bunch_crossing() const
{
    return (bunch_crossing);
}

// *****************************************************************************
void stub_CBC::set_fe_chip_ID(fe_chip_ID_t fe_chip_ID)
{
    this->fe_chip_ID = fe_chip_ID;

    return;
}

// *****************************************************************************
stub_CBC::fe_chip_ID_t stub_CBC::get_fe_chip_ID() const
{
    return (fe_chip_ID);
}

// *****************************************************************************
void stub_CBC::set_strip(strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
stub_CBC::strip_t stub_CBC::get_strip() const
{
    return (strip);
}

// *****************************************************************************
void stub_CBC::set_bend(bend_t bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
stub_CBC::bend_t stub_CBC::get_bend() const
{
    return (bend);
}

// *****************************************************************************
std::string stub_CBC::get_string() const
{
    std::stringstream out_string;

    out_string << "[";
    out_string << get_base_string();
    out_string << "]";

    return (out_string.str());
}

// *****************************************************************************
std::string stub_CBC::get_base_string() const
{
    std::stringstream out_string;

    out_string << std::hex
               << std::internal
               << std::setfill('0');
    out_string << "bx=0x" << std::setw(1) << bunch_crossing << ",";
    out_string << "cp=0x" << std::setw(1) << fe_chip_ID << ",";
    out_string << "s=0x"  << std::setw(2) << strip << ",";
    out_string << "b=0x"  << std::setw(2) << bend;

    return (out_string.str());
}
