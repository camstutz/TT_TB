/*!
 * @file stub_bxfsb.hpp
 * @author Christian Amstutz
 * @date June 30, 2014
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

#include "stub_bxsb.hpp"

// *****************************************************************************

template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_bxfsb;

template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace(sc_trace_file *tf,
        const stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits> &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_bxfsb : public stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>
{

public:
    typedef stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits> base;

    typedef typename base::bend_t bend_t;
    typedef typename base::bend_bv_t bend_bv_t;
    typedef typename base::strip_t strip_t;
    typedef typename base::strip_bv_t strip_bv_t;
    typedef unsigned int fechip_t;
    typedef sc_bv<fechip_bits> fechip_bv_t;
    typedef typename base::bx_t bx_t;
    typedef typename base::bx_bv_t bx_bv_t;
    typedef typename base::full_bv_t full_bv_t;

    static const unsigned int fechip_width = fechip_bits;

    static const unsigned int bend_start = 0;
    static const unsigned int strip_start = bend_start + base::bend_width;
    static const unsigned int fechip_start = strip_start + base::strip_width;
    static const unsigned int bx_start = fechip_start + fechip_width;

    /** Constructor: All member variables are set to 0 by default. */
    stub_bxfsb();
    stub_bxfsb(const bx_t bx, const fechip_t fechip, const strip_t strip,
            const bend_t bend);
    virtual ~stub_bxfsb();

    /** Setter function for the front end chip number */
    void set_fechip(const fechip_t fechip);

    /** Getter function for the front end chip number */
    fechip_t  get_fechip() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length();
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const stub_bxfsb& rhs) const;

    /** Assignment operator for stubs */
    stub_bxfsb& operator= (const stub_bxfsb& rhs);

protected:
    bool is_equal(const stub_bxfsb& rhs);
    void copy(const stub_bxfsb& original);

private:
    /** Front end chip number, indicating the FE chip on one side of a sensor
     *  module.
     */
    fechip_t fechip;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>::stub_bxfsb()
        : stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>(0, 0, 0)
{
    set_fechip(0);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>::stub_bxfsb(
        const bx_t bx, const fechip_t fechip, const strip_t strip,
        const bend_t bend) : stub_bxsb<bx_bits, strip_bits, bend_bits,
        total_bits>(bx, strip, bend)
{
    set_fechip(fechip);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
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
inline typename stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::fechip_t stub_bxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::get_fechip() const
{
    return (fechip);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
typename stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::full_bv_t stub_bxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::get_bitvector() const
{
    full_bv_t output_bv;

    output_bv(bx_start, bx_start+base::bx_width-1) = this->get_bx();
    output_bv(fechip_start, fechip_start+fechip_width-1) = get_fechip();
    output_bv(strip_start, strip_start+base::strip_width-1) = this->get_strip();
    output_bv(bend_start, bend_start+base::bend_width-1) = this->get_bend();

    return (output_bv);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void stub_bxfsb<bx_bits, fechip_bits, strip_bits,
        bend_bits, total_bits>::set_bitvector(full_bv_t bit_vector)
{
    set_bx(bit_vector(bx_start, bx_start+base::bx_width-1));
    set_frontend(bit_vector(fechip_start, fechip_start+fechip_width-1));
    set_strip(bit_vector(strip_start, strip_start+base::strip_width-1));
    set_bend(bit_vector(bend_start, bend_start+base::bend_width-1));

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline size_t stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::get_max_string_length()
{
    return (21);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
std::string stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "BX=" << this->get_bx()
                      << "FE=" << this->get_fechip()
                      << "S="  << this->get_strip()
                      << "B=" << this->get_bend() << "]";

    return (out_string);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::operator== (const stub_bxfsb<bx_bits, fechip_bits,
        strip_bits, bend_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits, total_bits>&
        stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::operator= (const stub_bxfsb<bx_bits, fechip_bits,
        strip_bits, bend_bits, total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::is_equal(const stub_bxfsb& rhs)
{
    bool equal = false;
    equal = equal & (base::equal(rhs));
    equal = equal & (fechip == rhs.get_fechip());

    return (equal);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_bxfsb<bx_bits, fechip_bits, strip_bits, bend_bits,
        total_bits>::copy(const stub_bxfsb& original)
{
    base::copy(original);
    set_fechip(original.get_fechip());

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_bxfsb<bx_bits, fechip_bits,
        strip_bits, bend_bits, total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.get_bx(), name + ".bx");
    sc_trace(tf, v.get_fechip(), name + ".fechip");
    sc_trace(tf, v.get_strip(), name + ".strip");
    sc_trace(tf, v.get_bend(), name + ".bend");

    return;
}
