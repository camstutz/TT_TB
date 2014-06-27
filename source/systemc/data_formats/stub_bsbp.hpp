/*!
 * @file stub_sb.hpp
 * @author Christian Amstutz
 * @date June 27, 2014
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

// *****************************************************************************

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
class stub_bsbp;

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
void sc_trace (sc_trace_file *tf, const stub_bsbp<bx_bits, strip_bits,
        bend_bits, pixel_bits> &v, const std::string &name);

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
ostream& operator << (ostream &os, stub_bsbp<bx_bits, strip_bits, bend_bits,
        pixel_bits> const &v);

// *****************************************************************************

/*!
 * @brief Representation of a stub with the fields strip and bend
 */
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
class stub_bsbp
{

public:
    static const unsigned int bx_width = bx_bits;
    static const unsigned int bend_width = bend_bits;
    static const unsigned int strip_width = strip_bits;
    static const unsigned int pixel_width = pixel_bits;
    static const unsigned int total_width = bx_bits + strip_bits +
            bend_bits + pixel_bits;

    static const unsigned int pixel_start = 0;
    static const unsigned int bend_start = pixel_start + pixel_bits;
    static const unsigned int strip_start = bend_start + bend_bits;
    static const unsigned int bx_start = strip_start + strip_bits;

    typedef sc_bv<pixel_bits> pixel_t;
    typedef sc_bv<bend_bits> bend_t;
    typedef sc_bv<strip_bits> strip_t;
    typedef sc_bv<bx_bits> bx_t;

    /** Constructor. The default values are 0 for the address and 0 for the
     * bend. */
    stub_bsbp(const bx_t bx=0, const strip_t strip=0, const bend_t bend=0,
            const pixel_t pixel=0);

    /** Setter function for the relative bunch crossing of the stub */
    void set_bx(const bx_t bunch_crossing);

    /** Getter function for the relative bunch crossing of the stub */
    bx_t  get_bx() const;

    /** Setter function for the strip address of the stub */
    void set_strip(const strip_t address);

    /** Getter function for the strip address of the stub */
    strip_t  get_strip() const;

    /** Setter function for the bend of the stub */
    void set_bend(const bend_t bend);

    /** Getter function for the bend of the stub */
    bend_t  get_bend() const;

    /** Setter function for the pixel address of the stub */
    void set_pixel(const pixel_t pixel);

    /** Getter function for the pixel address of the stub */
    pixel_t  get_pixel() const;

    /** Getter function for the whole stub as a bit vector */
    sc_bv<total_width> get_bit_vector() const;

    /** Comparison of two stub objects */
    bool operator == (const stub_bsbp &rhs) const;

    /** Assignment operator for stubs */
    stub_bsbp& operator = (const stub_bsbp & rhs);
    
    static size_t get_max_value_length();
    void get_string_value(char format_str, char* string_value);
    static void mti_debug_cb (void* var, char* mti_value, char format_str);

    /** Output function to print the address and bend of the stub. The format
     * is: [address,bend] */
    friend ostream& operator << <> (ostream &os, stub_bsbp const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace <> (sc_trace_file *tf, const stub_bsbp &v,
            const std::string &name);

private:

    /** Relative bunch crossing of the stub */
    bx_t bx;

    /** Strip address of the strip on the silicon detector */
    strip_t strip;

    /** represents the distance of the hits between the two silicon detectors */
    bend_t bend;

    /** Pixel address of the hits between the two silicon detectors */
    pixel_t pixel;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::stub_bsbp(const bx_t bx,
        const strip_t strip, const bend_t bend, const pixel_t pixel) :
        bx(bx),
        strip(strip),
        bend(bend),
        pixel(pixel)
{}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline void stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::set_bx(
        const bx_t bx)
{
    this->bx = bx;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline typename stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::bx_t
        stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::get_bx() const
{
    return (bx);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline void stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::set_strip(
        const strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline typename stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::strip_t
        stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::get_strip() const
{
    return (strip);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline void stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::set_bend(
        const bend_t bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline typename stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::bend_t
        stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::get_bend() const
{
    return (bend);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline void stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::set_pixel(
        const pixel_t pixel)
{
    this->pixel = pixel;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline typename stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::pixel_t
        stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::get_pixel() const
{
    return (pixel);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline sc_bv<stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::total_width>
        stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::get_bit_vector()
        const
{
    return ( (sc_bv<bx_width>(bx), sc_bv<strip_width>(strip),
            sc_bv<bend_width>(bend), sc_bv<pixel_width>(pixel)) );
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
inline bool stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::operator == (
        const stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits> &rhs) const
{
  return (rhs.bx == bx && rhs.strip == strip && rhs.bend == bend &&
          rhs.pixel == pixel);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>& stub_bsbp<bx_bits,
        strip_bits, bend_bits, pixel_bits>::operator = (const stub_bsbp<bx_bits,
        strip_bits, bend_bits, pixel_bits> & rhs)
{
    bx    = rhs.bx;
    strip = rhs.strip;
    bend  = rhs.bend;
    pixel = rhs.pixel;

    return (*this);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
size_t stub_bsbp<bx_bits, strip_bits, bend_bits,
        pixel_bits>::get_max_value_length()
{
    // todo: think about the return value of length
    return (25);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
void stub_bsbp<bx_bits, strip_bits, bend_bits,
        pixel_bits>::get_string_value(char format_str, char* string_value)
{
    std::stringstream my_string;
    //my_string << std::dec << strip << "," << bend;
    my_string << "test";
    std::strcpy (string_value, my_string.str().c_str());
    
    return;    
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
void stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>::mti_debug_cb(
        void* var, char* mti_value, char format_str)
{
    stub_bsbp<bx_bits, strip_bits, bend_bits, pixel_bits>* typed_var =
            reinterpret_cast<stub_bsbp<bx_bits, strip_bits, bend_bits,
            pixel_bits>* >(var);
    typed_var->get_string_value(format_str, mti_value);
    
    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
ostream& operator << (ostream &os, stub_bsbp<bx_bits, strip_bits, bend_bits,
        pixel_bits> const &v)
{
    os << std::hex;
    os << "[BX=" << v.bx.to_uint()
       << ",S=" << v.strip.to_uint()
       << ",B=" << v.bend.to_uint()
       << ",P=" << v.pixel.to_uint()
       << "]";

    return (os);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int pixel_bits>
void sc_trace (sc_trace_file *tf, const stub_bsbp<bx_bits, strip_bits,
        bend_bits, pixel_bits> &v, const std::string &name)
{
    sc_trace(tf, v.bx, name + ".bx");
    sc_trace(tf, v.strip, name + ".strip");
    sc_trace(tf, v.bend, name + ".bend");
    sc_trace(tf, v.pixel, name + ".pixel");

    return;
}
