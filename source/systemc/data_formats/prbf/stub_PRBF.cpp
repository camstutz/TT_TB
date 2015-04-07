/*!
 * @file stub_PRBF.cpp
 * @author Christian Amstutz
 * @date April 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_PRBF.hpp"

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************
stub_PRBF::stub_PRBF()
{
    set(0, 0, 0, 0, 0, 0);

    return;
}

// *****************************************************************************
stub_PRBF::stub_PRBF(fe_module_t fe_module, concentrator_ID_t concentrator_ID,
        fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend)
{
    set(fe_module, concentrator_ID, fe_chip_ID, strip, bend, 0);

    return;
}

// *****************************************************************************
stub_PRBF::stub_PRBF(fe_module_t fe_module, concentrator_ID_t concentrator_ID,
        fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z)
{
    set(fe_module, concentrator_ID, fe_chip_ID, strip, bend, z);

    return;
}

// *****************************************************************************
stub_PRBF::~stub_PRBF()
{}

// *****************************************************************************
void stub_PRBF::set(fe_module_t fe_module, concentrator_ID_t concentrator_ID,
        fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend)
{
    set(fe_module, concentrator_ID, fe_chip_ID, strip, bend, 0);
}

// *****************************************************************************
void stub_PRBF::set(fe_module_t fe_module, concentrator_ID_t concentrator_ID,
        fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z)
{
    set_fe_module(fe_module);
    set_concentrator_ID(concentrator_ID);
    set_fe_chip_ID(fe_chip_ID);
    set_strip(strip);
    set_bend(bend);
    set_z(z);

    return;
}

// *****************************************************************************
void stub_PRBF::set_fe_module(fe_module_t fe_module)
{
    this->fe_module = fe_module;

    return;
}

// *****************************************************************************
stub_PRBF::fe_module_t stub_PRBF::get_fe_module() const
{
    return (fe_module);
}

// *****************************************************************************
void stub_PRBF::set_concentrator_ID(concentrator_ID_t concentrator_ID)
{
    this->concentrator_ID = concentrator_ID;

    return;
}

// *****************************************************************************
stub_PRBF::concentrator_ID_t stub_PRBF::get_concentrator_ID() const
{
    return (concentrator_ID);
}

// *****************************************************************************
void stub_PRBF::set_fe_chip_ID(fe_chip_ID_t fe_chip_ID)
{
    this->fe_chip_ID = fe_chip_ID;

    return;
}

// *****************************************************************************
stub_PRBF::fe_chip_ID_t stub_PRBF::get_fe_chip_ID() const
{
    return (fe_chip_ID);
}

// *****************************************************************************
void stub_PRBF::set_strip(strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
stub_PRBF::strip_t stub_PRBF::get_strip() const
{
    return (strip);
}

// *****************************************************************************
void stub_PRBF::set_bend(bend_t bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
stub_PRBF::bend_t stub_PRBF::get_bend() const
{
    return (bend);
}

// *****************************************************************************
void stub_PRBF::set_z(z_t z)
{
    this->z = z;

    return;
}

// *****************************************************************************
stub_PRBF::z_t stub_PRBF::get_z() const
{
    return (z);
}

// *****************************************************************************
std::string stub_PRBF::get_PRBF_string() const
{
    std::stringstream out_string;

    out_string << std::hex
               << std::internal
               << std::setfill('0');
    out_string << "fe=0x" << std::setw(2) << fe_module << ",";
    out_string << "cc=0x" << std::setw(1) << concentrator_ID << ",";
    out_string << "cp=0x" << std::setw(1) << fe_chip_ID << ",";
    out_string << "s=0x"  << std::setw(2) << strip << ",";
    out_string << "b=0x"  << std::setw(1) << bend << ",";
    out_string << "z=0x"  << std::setw(1) << z;

    return (out_string.str());
}

// *****************************************************************************
} // namespace PRBF
