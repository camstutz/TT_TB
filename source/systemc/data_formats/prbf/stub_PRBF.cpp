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
    set_concentrator_ID(0);
    set_fe_chip_ID(0);
    set_strip(0);
    set_bend(0);
    set_z(0);

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
