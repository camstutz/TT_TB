/*!
 * @file hit.cpp
 * @author Christian Amstutz
 * @date June 23, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "hit.hpp"

// *****************************************************************************
hit::hit(const bunch_crossing_type bunch_crossing, const layer_type layer,
            const phi_type phi, const z_type z,
            const chip_number_type chip_number, hit_value* value)
{
    set_bunch_crossing(bunch_crossing);
    set_layer(layer);
    set_phi(phi);
    set_z(z);
    set_chip_number(chip_number);
    set_value(value);

    return;
}

// *****************************************************************************
hit::~hit()
{
    delete value;

    return;
}

// *****************************************************************************
hit::bunch_crossing_type hit::get_bunch_crossing()
{
    return(bunch_crossing);
}

// *****************************************************************************
hit::layer_type hit::get_layer()
{
    return(layer);
}

// *****************************************************************************
hit::phi_type hit::get_phi()
{
    return(phi);
}

// *****************************************************************************
hit::z_type hit::get_z()
{
    return(z);
}

// *****************************************************************************
hit::chip_number_type hit::get_chip_number()
{
    return(chip_number);
}

// *****************************************************************************
hit_value* hit::get_value()
{
    return(value);
}

// *****************************************************************************
void hit::set_bunch_crossing(const bunch_crossing_type bunch_crossing)
{
    this->bunch_crossing = bunch_crossing;

    return;
}

// *****************************************************************************
void hit::set_layer(const layer_type layer)
{
    this->layer = layer;

    return;
}

// *****************************************************************************
void hit::set_phi(const phi_type phi)
{
    this->phi = phi;

    return;
}

// *****************************************************************************
void hit::set_z(const z_type z)
{
    this->z = z;

    return;
}

// *****************************************************************************
void hit::set_chip_number(const chip_number_type chip_number)
{
    this->chip_number = chip_number;

    return;
}

// *****************************************************************************
void hit::set_value(hit_value* value)
{
    this->value = value;

    return;
}
