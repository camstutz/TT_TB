/*!
 * @file stub_MPA.cpp
 * @author Christian Amstutz
 * @date April 24, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_MPA.hpp"

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
stub_MPA::stub_MPA() :
        stub_CBC(0, 0, 0, 0)
{
    set_z(0);

    return;
}

// *****************************************************************************
stub_MPA::stub_MPA(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chip_ID,
        strip_t strip, bend_t bend, z_t z) :
        stub_CBC (bunch_crossing, fe_chip_ID, strip, bend)
{
    set_z(z);

    return;
}

// *****************************************************************************
stub_MPA::~stub_MPA()
{}

// *****************************************************************************
void stub_MPA::set(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chip_ID,
        strip_t strip, bend_t bend, z_t z)
{
    stub_CBC::set(bunch_crossing, fe_chip_ID, strip, bend);
    set_z(z);

    return;
}

// *****************************************************************************
void stub_MPA::set_z(z_t z)
{
    this->z = z;

    return;
}

// *****************************************************************************
stub_MPA::z_t stub_MPA::get_z() const
{
    return (z);
}

// *****************************************************************************
bool stub_MPA::operator== (const stub_MPA& rhs) const
{
    bool equal = true;

    equal &= (stub_CBC::operator== (rhs));
    equal &= (rhs.z == z);

    return (equal);
}

// *****************************************************************************
std::string stub_MPA::get_string() const
{
    std::stringstream out_string;

    out_string << "[";
    out_string << stub_CBC::get_base_string();
    out_string << ",";
    out_string << std::hex
               << std::internal
               << std::setfill('0');
    out_string << "z=0x"  << std::setw(1) << z;
    out_string << "]";

    return (out_string.str());
}

// *****************************************************************************
} // namespace CIC
