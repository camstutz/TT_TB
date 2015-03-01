/*!
 * @file stub_vbxfsb.hpp
 * @author Christian Amstutz
 * @date February 25, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>
#include <sstream>
#include <iostream>

#include <systemc.h>

#include "stub_bxsb.hpp"

// *****************************************************************************

template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_vbxfsb;

template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace(sc_trace_file *tf,
        const stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits> &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_vbxfsb : public stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits+1>
{

public:
    typedef stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits+1> base;

    typedef typename base::bend_t bend_t;
    typedef typename base::bend_bv_t bend_bv_t;
    typedef typename base::strip_t strip_t;
    typedef typename base::strip_bv_t strip_bv_t;
    typedef unsigned int fechip_t;
    typedef sc_bv<fechip_bits> fechip_bv_t;
    typedef typename base::bx_t bx_t;
    typedef typename base::bx_bv_t bx_bv_t;
    typedef bool valid_t;
    typedef bool valid_bv_t;
    typedef typename base::full_bv_t full_bv_t;

    static const unsigned int fechip_width = fechip_bits;
    static const unsigned int valid_width = 1;

    static const unsigned int bend_start = 0;
    static const unsigned int strip_start = bend_start + base::bend_width;
    static const unsigned int fechip_start = strip_start + base::strip_width;
    static const unsigned int bx_start = fechip_start + fechip_width;
    static const unsigned int valid_start = bx_start + base::bx_width;

    /** Constructor: All member variables are set to 0 by default. */
    stub_vbxfsb();
    stub_vbxfsb(const valid_t valid, const bx_t bx, const fechip_t fechip,
            const strip_t strip, const bend_t bend);
    stub_vbxfsb(const base fe_stub);
    virtual ~stub_vbxfsb();

    /** Setter function for the data valid bit */
    void set_valid(const valid_t valid);

    /** Getter function for the data valid bit */
    valid_t  get_valid() const;

    /** Setter function for the front end chip number */
    void set_fechip(const fechip_t fechip);

    /** Getter function for the front end chip number */
    fechip_t  get_fechip() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length();
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const stub_vbxfsb& rhs) const;

    /** Assignment operator for stubs */
    stub_vbxfsb& operator= (const stub_vbxfsb& rhs);

protected:
    /** Data valid bit for the stub */
    valid_t valid;

    /** Front end chip number, indicating the FE chip on one side of a sensor
     *  module.
     */
    fechip_t fechip;

    bool is_equal(const stub_vbxfsb& rhs);
    void copy(const stub_vbxfsb& original);
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>::stub_vbxfsb()
        : stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::base(0, 0, 0)
{
    set_valid(0);
    set_fechip(0);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>::stub_vbxfsb(
        const valid_t valid, const bx_t bx, const fechip_t fechip,
        const strip_t strip, const bend_t bend) : stub_vbxfsb<bx_bits,
        fechip_bits, strip_bits, bend_bits, total_bits>::base(bx, strip, bend)
{
    set_valid(valid);
    set_fechip(fechip);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>::stub_vbxfsb(
		const base fe_stub) : stub_vbxfsb<bx_bits, fechip_bits, strip_bits,
		bend_bits, total_bits>::base(0, fe_stub.strip, fe_stub.bend)
{
	set_valid(0);
	set_fechip(0);

	return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::~stub_vbxfsb()
{}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::set_valid(const valid_t valid)
{
    this->valid = valid;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline typename stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::valid_t stub_vbxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::get_valid() const
{
    return (valid);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::set_fechip(const fechip_t fechip)
{
    // todo: check range
    this->fechip = fechip;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline typename stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::fechip_t stub_vbxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::get_fechip() const
{
    return (fechip);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
typename stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::full_bv_t stub_vbxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::get_bitvector() const
{
    full_bv_t output_bv;

    output_bv(valid_start+valid_width-1, valid_start) = this->get_valid();
    output_bv(bx_start+base::bx_width-1, bx_start) = this->get_bx();
    output_bv(fechip_start+fechip_width-1, fechip_start) = get_fechip();
    output_bv(strip_start+base::strip_width-1, strip_start) = this->get_strip();
    output_bv(bend_start+base::bend_width-1, bend_start) = this->get_bend();

    return (output_bv);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void stub_vbxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::set_bitvector(full_bv_t bit_vector)
{
    this->set_valid(bit_vector(valid_start+valid_width-1, valid_start).to_uint());
    this->set_bx(bit_vector(bx_start+base::bx_width-1, bx_start).to_uint());
    this->set_fechip(bit_vector(fechip_start+fechip_width-1, fechip_start).to_uint());
    this->set_strip(bit_vector(strip_start+base::strip_width-1, strip_start).to_uint());
    this->set_bend(bit_vector(bend_start+base::bend_width-1, bend_start).to_uint());

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline size_t stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::get_max_string_length()
{
    // todo: make dependent on fields of stub
    return (24);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
std::string stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "V="  << std::noboolalpha << this->get_valid()
                      << "BX=" << this->get_bx()
                      << "FE=" << this->get_fechip()
                      << "S="  << this->get_strip()
                      << "B="  << this->get_bend() << "]";

    return (out_string.str());
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::operator== (const stub_vbxfsb<bx_bits, fechip_bits,
        strip_bits, bend_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>&
        stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::operator= (const stub_vbxfsb<bx_bits, fechip_bits,
        strip_bits, bend_bits, total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::is_equal(const stub_vbxfsb& rhs)
{
    bool equal = false;
    equal = equal & (base::equal(rhs));
    equal = equal & (fechip == rhs.get_fechip());
    equal = equal & (valid == rhs.get_valid());

    return (equal);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_vbxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::copy(const stub_vbxfsb& original)
{
    base::copy(original);
    set_fechip(original.get_fechip());
    set_valid(original.get_valid());

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_vbxfsb<bx_bits, fechip_bits,
        strip_bits, bend_bits, total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.valid, name + ".valid");
    sc_trace(tf, v.bx, name + ".bx");
    sc_trace(tf, v.fechip, name + ".fechip");
    sc_trace(tf, v.strip, name + ".strip");
    sc_trace(tf, v.bend, name + ".bend");

    return;
}
