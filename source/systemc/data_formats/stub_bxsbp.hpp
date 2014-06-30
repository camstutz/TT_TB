/*!
 * @file stub_bxsbp.hpp
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

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
class stub_bxsbp;

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
void sc_trace(sc_trace_file *tf, const stub_bxsbp<bx_bits, strip_bits,
        bend_bits, pixel_bits, total_bits> &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
class stub_bxsbp : public stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>
{

public:
    typedef stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits> base;

    static const unsigned int pixel_width = pixel_bits;

    static const unsigned int pixel_start = 0;
    static const unsigned int bend_start = pixel_start + pixel_width;
    static const unsigned int strip_start = bend_start + base::bend_width;
    static const unsigned int bx_start = strip_start + base::strip_width;

    typedef unsigned int pixel_t;
    typedef sc_bv<pixel_bits> pixel_bv_t;

    /** Constructor: All member variables are set to 0 by default. */
    stub_bxsbp();
    stub_bxsbp(const bx_t bx, const strip_t strip, const bend_t bend,
            const pixel_t pixel);
    virtual ~stub_bxsbp();

    /** Setter function for the front end chip number */
    void set_pixel(const fechip_t pixel);

    /** Getter function for the front end chip number */
    pixel_t  get_pixel() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length();
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const stub_bxsbp& rhs) const;

    /** Assignment operator for stubs */
    stub_bxsbp& operator= (const stub_bxsbp& rhs);

protected:
    bool is_equal(const stub_bxsbp& rhs);
    void copy(const stub_bxsbp& original);

private:
    /** Front end chip number, indicating the FE chip on one side of a sensor
     *  module.
     */
    pixel_t pixel;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits, total_bits>::stub_bxsbp()
        : stub_bxsb(0, 0, 0)
{
    set_pixel(0);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits, total_bits>::stub_bxsbp(
        const bx_t bx, const strip_t strip, const bend_t bend, const pixel_t
        pixel) : stub_bxsb(bx, strip, bend)
{
    set_pixel(pixel);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
inline void stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::set_fechip(const fechip_t fechip)
{
    // todo: check range
    this->pixel = pixel;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
inline typename stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::fechip_t stub_bxsbp<bx_bits, strip_bits, bend_bits,
        pixel_bits, total_bits>::get_fechip() const
{
    return (pixel);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
virtual stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::full_bv_t stub_bxsbp<bx_bits, strip_bits, bend_bits,
        pixel_bits, total_bits>::get_bitvector() const
{
    full_bv_t output_bv;

    output_bv(bx_start, bx_start+bx_width-1) = get_bx();
    output_bv(strip_start, strip_start+strip_width-1) = get_strip();
    output_bv(bend_start, bend_start+bend_width-1) = get_bend();
    output_bv(pixel_start, pixel_start+pixel_width-1) = get_pixel();

    return (output_bv);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
virtual void stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::set_bitvector(full_bv_t bit_vector)
{
    set_bx(bit_vector(bx_start, bx_start+bx_width-1));
    set_strip(bit_vector(strip_start, strip_start+strip_width-1));
    set_bend(bit_vector(bend_start, bend_start+bend_width-1));
    set_pixel(bit_vector(pixel_start, pixel_start+pixel_width-1));

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
virtual inline size_t stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::get_max_string_length()
{
    return (21);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
virtual std::string stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::get_string() const
{
    std::stringstream out_string;
    out_string << "[" "BX=" << bx << "S=" << strip << "B=" << bend
               << "P=" << fechip << "]";

    return (out_string);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
inline bool stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::operator== (const stub_bxsbp<bx_bits, strip_bits,
        bend_bits, pixel_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
inline stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits, total_bits>&
stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits, total_bits>::operator= (
        const stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
inline bool stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::is_equal(const stub_bxsbp& rhs)
{
    bool equal = false;
    equal = equal & (base::equal(rhs));
    equal = equal & (pixel == rhs.get_pixel());

    return (equal);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
inline void stub_bxsbp<bx_bits, strip_bits, bend_bits, pixel_bits,
        total_bits>::copy(const stub_bxsbp& original)
{
    base::copy(original);
    set_pixel(original.get_pixel());

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits, unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_bxsbp<bx_bits, strip_bits,
        bend_bits, pixel_bits, total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.get_bx(), name + ".bx");
    sc_trace(tf, v.get_strip(), name + ".strip");
    sc_trace(tf, v.get_bend(), name + ".bend");
    sc_trace(tf, v.get_pixel(), name + ".pixel");

    return;
}
