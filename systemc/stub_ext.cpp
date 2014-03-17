/*!
 * @file stub_ext.cpp
 * @author Christian Amstutz
 * @date Mar 17, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "stub_ext.hpp"

// *****************************************************************************
stub_ext::stub_ext()
{
    set_phi_coord(0);
    set_z_coord(0);
    set_fechip_nr(0);
    set_strip_nr(0);

    return;
}

// *****************************************************************************
inline void stub_ext::set_phi_coord(const phi_coord_t phi_coord)
{
    this->phi_coord = phi_coord;

    return;
}

// *****************************************************************************
inline stub_ext::phi_coord_t stub_ext::get_phi_coord() const
{
    return (phi_coord);
}

// *****************************************************************************
inline void stub_ext::set_z_coord(const z_coord_t z_coord)
{
    this->z_coord = z_coord;

    return;
}

// *****************************************************************************
inline stub_ext::z_coord_t stub_ext::get_z_coord() const
{
    return (z_coord);
}

// *****************************************************************************
inline void stub_ext::set_fechip_nr(const fechip_nr_t address)
{
    this->fechip_nr = address;

    return;
}

// *****************************************************************************
inline stub_ext::fechip_nr_t stub_ext::get_fechip_nr() const
{
    return (fechip_nr);
}

// *****************************************************************************
inline void stub_ext::set_strip_nr(const strip_nr_t address)
{
    this->strip_nr = address;

    return;
}

// *****************************************************************************
inline stub_ext::strip_nr_t stub_ext::get_strip_nr() const
{
  return (strip_nr);
}

// *****************************************************************************
sc_bv<stub_ext::stub_width> stub_ext::getBitVector() const
{
    sc_bv<stub_width> full_stub;
    full_stub = ( (phi_coord, z_coord, fechip_nr, strip_nr) );

    return (full_stub);
}

// *****************************************************************************
bool stub_ext::operator == (const stub_ext &rhs) const
{
    bool equality = true;
    equality = equality && (rhs.phi_coord == phi_coord);
    equality = equality && (rhs.z_coord == z_coord);
    equality = equality && (rhs.fechip_nr == fechip_nr);
    equality = equality && (rhs.strip_nr == strip_nr);

    return (equality);
}

// *****************************************************************************
stub_ext& stub_ext::operator = (const stub_ext & rhs)
{
    phi_coord = rhs.phi_coord;
    z_coord = rhs.z_coord;
    fechip_nr = rhs.fechip_nr;
    strip_nr = rhs.strip_nr;

    return (*this);
}

// *****************************************************************************
ostream& operator << (ostream &os, stub_ext const &v)
{
    os << "[phi=" << std::hex
            << v.phi_coord.to_uint() << ",Z="
            << v.z_coord.to_uint() << ",FE="
            << v.fechip_nr.to_uint() << ",str="
            << v.strip_nr.to_uint()
            << "]";

    return (os);
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const stub_ext &v, const std::string &name)
{
    sc_trace(tf, v.phi_coord, name + ".phi_coord");
    sc_trace(tf, v.z_coord, name + ".z_coord");
    sc_trace(tf, v.fechip_nr, name + ".fechip_nr");
    sc_trace(tf, v.strip_nr, name + ".strip_nr");

    return;
}
