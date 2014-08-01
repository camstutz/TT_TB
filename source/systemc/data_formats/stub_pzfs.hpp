/*!
 * @file stub_pzfs.hpp
 * @author Christian Amstutz
 * @date July 31, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <iostream>

#include <systemc.h>

#include "multifield_base.hpp"

// *****************************************************************************

template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
class stub_pzfs;

template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
void sc_trace(sc_trace_file *tf,
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits, total_bits>
        &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
class stub_pzfs : public multifield_base<total_bits>
{

public:
    typedef multifield_base<total_bits> base;

    typedef unsigned int strip_t;
    typedef sc_bv<strip_bits> strip_bv_t;
    typedef unsigned int fechip_t;
    typedef sc_bv<fechip_bits> fechip_bv_t;
    typedef unsigned int z_t;
    typedef sc_bv<z_bits> z_bv_t;
    typedef unsigned int phi_t;
    typedef sc_bv<phi_bits> phi_bv_t;
    typedef typename base::full_bv_t full_bv_t;

    static const unsigned int strip_width = strip_bits;
    static const unsigned int fechip_width = fechip_bits;
    static const unsigned int z_width = z_bits;
    static const unsigned int phi_width = phi_bits;

    static const unsigned int strip_start = 0;
    static const unsigned int fechip_start = strip_start + strip_bits;
    static const unsigned int z_start = fechip_start + fechip_bits;
    static const unsigned int phi_start = z_start + z_bits;

    /** Constructor: All member variables are by default set to 0. */
    stub_pzfs(const phi_t phi=0, const z_t z=0, const fechip_t fechip=0,
            const strip_t strip=0);

    virtual ~stub_pzfs();

    /** Setter function for the phi coordinate */
    void set_phi(const phi_t phi);

    /** Getter function for the phi coordinate */
    phi_t  get_phi() const;

    /** Setter function for the z coordinate */
    void set_z(const z_t z);

    /** Getter function for the z coordinate */
    z_t  get_z() const;

    /** Setter function for the front end chip number */
    void set_fechip(const fechip_t fechip);

    /** Getter function for the front end chip number */
    fechip_t  get_fechip() const;

    /** Setter function for the strip number */
    void set_strip(const strip_t strip);

    /** Getter function for the strip number */
    strip_t  get_strip() const;

    /** Getter function for the whole stub as a bit vector */
    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length() const;
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const stub_pzfs &rhs) const;

    /** Assignment operator for stubs */
    stub_pzfs& operator= (const stub_pzfs & rhs);

private:

    /** Phi coordinate from which the extended stub originates */
    phi_t phi;

    /** Z coordinate from which the extended stub originates */
    z_t z;

    /** Front End Chip number from which the extended stub originates */
    fechip_t fechip;

    /** Strip number from which the extended stub originates */
    strip_t strip;

protected:
    bool is_equal(const stub_pzfs& rhs) const;
    void copy(const stub_pzfs& original);

/** Function for tracing support in SystemC */
friend void sc_trace <> (sc_trace_file *tf, const stub_pzfs &v,
        const std::string &name);
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits, total_bits>::stub_pzfs(
        const phi_t phi, const z_t z, const fechip_t fechip,
        const strip_t strip)
{
    set_phi(phi);
    set_z(z);
    set_fechip(fechip);
    set_strip(strip);

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits, total_bits>::~stub_pzfs()
{}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::set_phi(const phi_t phi)
{
    this->phi = phi;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::phi_t stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::get_phi() const
{
    return (phi);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::set_z(const z_t z)
{
    this->z = z;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::z_t stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::get_z() const
{
    return (z);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::set_fechip(const fechip_t fechip)
{
    this->fechip = fechip;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::fechip_t stub_pzfs<phi_bits, z_bits, fechip_bits,
        strip_bits, total_bits>::get_fechip() const
{
    return (fechip);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::set_strip(const strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::strip_t stub_pzfs<phi_bits, z_bits, fechip_bits,
        strip_bits, total_bits>::get_strip() const
{
  return (strip);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::full_bv_t stub_pzfs<phi_bits, z_bits, fechip_bits,
        strip_bits, total_bits>::get_bitvector() const
{
    full_bv_t output_bv;

    output_bv(phi_start+phi_width-1, phi_start) = this->get_phi();
    output_bv(z_start+z_width-1, z_start) = this->get_z();
    output_bv(fechip_start+fechip_width-1, fechip_start) = this->get_fechip();
    output_bv(strip_start+strip_width-1, strip_start) = this->get_strip();

    return (output_bv);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::set_bitvector(full_bv_t bit_vector)
{
    this->set_phi(bit_vector(phi_start+phi_width-1, phi_start).to_uint());
    this->set_z(bit_vector(z_start+z_width-1, z_start).to_uint());
    this->set_fechip(bit_vector(fechip_start+fechip_width-1, fechip_start).to_uint());
    this->set_strip(bit_vector(strip_start+strip_width-1, strip_start).to_uint());

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline size_t stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::get_max_string_length() const
{
    // todo: relative to widths of fields
    return (22);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
std::string stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "P=" << this->get_phi()
                      << "Z=" << this->get_z()
                      << "F=" << this->get_fechip()
                      << "S=" << this->get_strip() << "]";

    return (out_string.str());
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
bool stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::operator == (const stub_pzfs<phi_bits, z_bits, fechip_bits,
        strip_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits, total_bits>& stub_pzfs<
        phi_bits, z_bits, fechip_bits, strip_bits, total_bits>::operator= (
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits, total_bits>
        & rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline bool stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::is_equal(const stub_pzfs& rhs) const
{
    bool equal = false;
    equal = equal & (phi == rhs.get_phi());
    equal = equal & (z == rhs.get_z());
    equal = equal & (fechip == rhs.get_fechip());
    equal = equal & (strip == rhs.get_strip());

    return (equal);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits,
        total_bits>::copy(const stub_pzfs& original)
{
    set_phi(original.get_phi());
    set_z(original.get_z());
    set_fechip(original.get_fechip());
    set_strip(original.get_strip());

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_pzfs<phi_bits, z_bits, fechip_bits,
        strip_bits, total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.phi, name + ".phi");
    sc_trace(tf, v.z, name + ".z");
    sc_trace(tf, v.fechip, name + ".fechip");
    sc_trace(tf, v.strip, name + ".strip");

    return;
}
