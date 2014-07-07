/*!
 * @file stub_bxpsb.hpp
 * @author Christian Amstutz
 * @date July 4, 2014
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

template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
class stub_bxsbp;

template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
void sc_trace(sc_trace_file *tf, const stub_bxsbp<bx_bits, pixel_bits,
        strip_bits, bend_bits, total_bits> &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
class stub_bxpsb : public stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>
{

public:
    typedef stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits> base;

    typedef unsigned int pixel_t;
    typedef sc_bv<pixel_bits> pixel_bv_t;
    typedef typename base::bend_t bend_t;
    typedef typename base::bend_bv_t bend_bv_t;
    typedef typename base::strip_t strip_t;
    typedef typename base::strip_bv_t strip_bv_t;
    typedef typename base::bx_t bx_t;
    typedef typename base::bx_bv_t bx_bv_t;
    typedef typename base::full_bv_t full_bv_t;

    static const unsigned int pixel_width = pixel_bits;

    static const unsigned int bend_start = 0;
    static const unsigned int strip_start = bend_start + base::bend_width;
    static const unsigned int pixel_start = strip_start + base::strip_width;
    static const unsigned int bx_start = pixel_start + pixel_width;

    /** Constructor: All member variables are set to 0 by default. */
    stub_bxpsb();
    stub_bxpsb(const bx_t bx, const pixel_t pixel, const strip_t strip,
            const bend_t bend);
    virtual ~stub_bxpsb();

    /** Setter function for the front end chip number */
    void set_pixel(const pixel_t pixel);

    /** Getter function for the front end chip number */
    pixel_t  get_pixel() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length() const;
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const stub_bxpsb& rhs) const;

    /** Assignment operator for stubs */
    stub_bxpsb& operator= (const stub_bxpsb& rhs);

    friend void sc_trace <> (sc_trace_file *tf, const stub_bxsbp<bx_bits, pixel_bits, strip_bits, bend_bits, total_bits> &v, const std::string &name);

    // todo: make them at least protected
public:
    /** Front end chip number, indicating the FE chip on one side of a sensor
     *  module.
     */
    pixel_t pixel;

protected:
    bool is_equal(const stub_bxpsb& rhs) const;
    void copy(const stub_bxpsb& original);
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits, total_bits>::stub_bxpsb()
        : stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>(0, 0, 0)
{
    set_pixel(0);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits, total_bits>::stub_bxpsb(
        const bx_t bx, const pixel_t pixel, const strip_t strip,
        const bend_t bend) : stub_bxsb<bx_bits, strip_bits, bend_bits,
        total_bits>(bx, strip, bend)
{
    set_pixel(pixel);

    return;
}


// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::~stub_bxpsb()
{}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline void stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::set_pixel(const pixel_t pixel)
{
    // todo: check range
    this->pixel = pixel;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline typename stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::pixel_t stub_bxpsb<bx_bits, pixel_bits, strip_bits,
        bend_bits, total_bits>::get_pixel() const
{
    return (pixel);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
typename stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits, total_bits>::full_bv_t
        stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::get_bitvector() const
{
    full_bv_t output_bv;

    output_bv(bx_start+base::bx_width-1, bx_start) = this->get_bx();
    output_bv(pixel_start+pixel_width-1, pixel_start) = this->get_pixel();
    output_bv(strip_start+base::strip_width-1, strip_start) = this->get_strip();
    output_bv(bend_start+base::bend_width-1, bend_start) = this->get_bend();

    return (output_bv);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
void stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::set_bitvector(full_bv_t bit_vector)
{
    this->set_bx(bit_vector(bx_start+base::bx_width-1, bx_start).to_uint());
    this->set_pixel(bit_vector(pixel_start+pixel_width-1, pixel_start).to_uint());
    this->set_strip(bit_vector(strip_start+base::strip_width-1, strip_start).to_uint());
    this->set_bend(bit_vector(bend_start+base::bend_width-1, bend_start).to_uint());

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline size_t stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::get_max_string_length() const
{
    // todo: relative to widths of fields
    return (21);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
std::string stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "BX=" << this->get_bx()
                      << "P="  << this->get_pixel()
                      << "S="  << this->get_strip()
                      << "B="  << this->get_bend() << "]";

    return (out_string.str());
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline bool stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::operator== (const stub_bxpsb<bx_bits, pixel_bits,
        strip_bits, bend_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits, total_bits>&
stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits, total_bits>::operator= (
        const stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline bool stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::is_equal(const stub_bxpsb& rhs) const
{
    bool equal = false;
    equal = equal & (base::is_equal(rhs));
    equal = equal & (pixel == rhs.get_pixel());

    return (equal);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
inline void stub_bxpsb<bx_bits, pixel_bits, strip_bits, bend_bits,
        total_bits>::copy(const stub_bxpsb& original)
{
    base::copy(original);
    set_pixel(original.get_pixel());

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int pixel_bits, unsigned int strip_bits,
        unsigned int bend_bits, unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_bxpsb<bx_bits, pixel_bits,
        strip_bits, bend_bits, total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.bx, name + ".bx");
    sc_trace(tf, v.strip, name + ".strip");
    sc_trace(tf, v.bend, name + ".bend");
    sc_trace(tf, v.pixel, name + ".pixel");

    return;
}
