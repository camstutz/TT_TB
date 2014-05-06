/*!
 * @file stub_pzfs.hpp
 * @author Christian Amstutz
 * @date May 6, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <string>
#include <iostream>

#include <systemc.h>

// *****************************************************************************

template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
class stub_pzfs;

template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
ostream& operator << (ostream &os,
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits> &v);

template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
void sc_trace(sc_trace_file *tf,
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits> &v,
        const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
class stub_pzfs
{
    static_assert (phi_bits > 0,
            "phi_bits must be at least 1 bit wide.");
    static_assert (z_bits > 0,
            "z_bits must be at least 1 bit wide.");
    static_assert (fechip_bits > 0,
            "fechip_bits must be at least 1 bit wide.");
    static_assert (strip_bits > 0,
            "strip_bits must be at least 1 bit wide.");

public:
    static constexpr unsigned int strip_width = strip_bits;
    static constexpr unsigned int fechip_width = fechip_bits;
    static constexpr unsigned int z_width = z_bits;
    static constexpr unsigned int phi_width = phi_bits;
    static constexpr unsigned int total_width = phi_bits + z_bits +
            fechip_bits + strip_bits;

    static constexpr unsigned int strip_start = 0;
    static constexpr unsigned int fechip_start = strip_start + strip_bits;
    static constexpr unsigned int z_start = fechip_start + fechip_bits;
    static constexpr unsigned int phi_start = z_start + z_bits;

    typedef sc_bv<strip_bits> strip_t;
    typedef sc_bv<fechip_bits> fechip_t;
    typedef sc_bv<z_bits> z_t;
    typedef sc_bv<phi_bits> phi_t;

    /** Constructor: All member variables are by default set to 0. */
    stub_pzfs(const phi_t phi=0, const z_t z=0, const fechip_t fechip=0,
            const strip_t strip=0);

    /** Constructor: Creates the stub out of a bit vector */
    stub_pzfs(const sc_bv<total_width> bit_vector);

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
    sc_bv<total_width> get_bit_vector() const;

    /** Comparison of two extended stub objects */
    bool operator == (const stub_pzfs &rhs) const;

    /** Assignment operator for extended stubs */
    stub_pzfs& operator = (const stub_pzfs & rhs);

    /** Output function to print the address and bend of the extended stub. The
     * format is: [phi,z,fechip,strip] */
    friend ostream& operator << <> (ostream &os, const stub_pzfs &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace <> (sc_trace_file *tf, const stub_pzfs &v,
            const std::string &name);

private:

    /** Phi coordinate from which the extended stub originates */
    phi_t phi;

    /** Z coordinate from which the extended stub originates */
    z_t z;

    /** Front End Chip number from which the extended stub originates */
    fechip_t fechip;

    /** Strip number from which the extended stub originates */
    strip_t strip;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::stub_pzfs(const phi_t phi,
        const z_t z, const fechip_t fechip, const strip_t strip) :
        phi(phi),
        z(z),
        fechip(fechip),
        strip(strip)
{
    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::stub_pzfs(
		const sc_bv<total_width> bit_vector)
{
	set_phi(bit_vector(total_width-1,phi_start));
	set_z(bit_vector(phi_start-1, z_start));
	set_fechip(bit_vector(z_start-1, fechip_start));
	set_strip(bit_vector(fechip_start-1, strip_start));

	return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::set_phi(
        const phi_t phi)
{
    this->phi = phi;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::phi_t
        stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::get_phi() const
{
    return (phi);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::set_z(
        const z_t z)
{
    this->z = z;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::z_t
        stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::get_z() const
{
    return (z);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::set_fechip(
        const fechip_t fechip)
{
    this->fechip = fechip;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::fechip_t
        stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::get_fechip() const
{
    return (fechip);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline void stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::set_strip(
        const strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
inline typename stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::strip_t
        stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::get_strip() const
{
  return (strip);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
sc_bv<stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::total_width>
        stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::get_bit_vector()
        const
{
    sc_bv<total_width> full_stub;
    full_stub = ( (phi, z, fechip, strip) );

    return (full_stub);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
bool stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>::operator == (
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits> &rhs) const
{
    bool equality = true;
    equality = equality && (rhs.phi == phi);
    equality = equality && (rhs.z == z);
    equality = equality && (rhs.fechip == fechip);
    equality = equality && (rhs.strip == strip);

    return (equality);
}

// *****************************************************************************
template<unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits>& stub_pzfs<phi_bits,
        z_bits, fechip_bits, strip_bits>::operator = (
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits> & rhs)
{
    phi = rhs.phi;
    z = rhs.z;
    fechip = rhs.fechip;
    strip = rhs.strip;

    return (*this);
}

// *****************************************************************************
template <unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
ostream& operator << (ostream &os,
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits> &v)
{
    os << "[P=" << std::hex
            << v.phi.to_uint() << ",Z="
            << v.z.to_uint() << ",F="
            << v.fechip.to_uint() << ",S="
            << v.strip.to_uint()
            << "]";

    return (os);
}

// *****************************************************************************
template <unsigned int phi_bits, unsigned int z_bits, unsigned int fechip_bits,
        unsigned int strip_bits>
void sc_trace (sc_trace_file *tf,
        const stub_pzfs<phi_bits, z_bits, fechip_bits, strip_bits> &v,
        const std::string &name)
{
    sc_trace(tf, v.phi, name + ".phi");
    sc_trace(tf, v.z, name + ".z");
    sc_trace(tf, v.fechip, name + ".fechip");
    sc_trace(tf, v.strip, name + ".strip");

    return;
}
