/*!
 * @file hit.hpp
 * @author Christian Amstutz
 * @date June 16, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include "hit_value.hpp"

// todo: add error handling for the ranges of the member variables

/*!
 * @brief
 */
class hit
{
public:
    typedef unsigned int bunch_crossing_type;
    typedef unsigned int layer_type;
    typedef unsigned int phi_type;
    typedef unsigned int z_type;
    typedef unsigned int chip_number_type;

    hit(const bunch_crossing_type bunch_crossing, const layer_type layer,
            const phi_type phi, const z_type z,
            const chip_number_type chip_number, hit_value* value);
    ~hit();

    bunch_crossing_type get_bunch_crossing();
    layer_type get_layer();
    phi_type get_phi();
    z_type get_z();
    chip_number_type get_chip_number();
    hit_value* get_value();

private:
    bunch_crossing_type bunch_crossing;
    layer_type layer;
    phi_type phi;
    z_type z;
    chip_number_type chip_number;
    hit_value* value;

    void set_bunch_crossing(const bunch_crossing_type bunch_crossing);
    void set_layer(const layer_type layer);
    void set_phi(const phi_type phi);
    void set_z(const z_type z);
    void set_chip_number(const chip_number_type chip_number);
    void set_value(hit_value* value);
};
