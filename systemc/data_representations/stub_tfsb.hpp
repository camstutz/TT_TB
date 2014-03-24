/*!
 * @file stub_tfsb.hpp
 * @author Christian Amstutz
 * @date Mar 24, 2014
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

template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
class stub_tfsb;

template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
ostream& operator << (ostream &os,
        const stub_tfsb<timestamp_bits, fechip_bits, strip_bits, bend_bits> &v);

template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
void sc_trace(sc_trace_file *tf,
        const stub_tfsb<timestamp_bits, fechip_bits, strip_bits, bend_bits> &v,
        const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
class stub_tfsb
{
public:
    // todo: check for the correct range of template parameters, must be larger than 0

    static constexpr unsigned int bend_width = bend_bits;
    static constexpr unsigned int strip_width = strip_bits;
    static constexpr unsigned int fechip_width = fechip_bits;
    static constexpr unsigned int timestamp_width = timestamp_bits;
    static constexpr unsigned int total_width = timestamp_bits + fechip_bits +
            strip_bits + bend_bits;

    static constexpr unsigned int bend_start = 0;
    static constexpr unsigned int strip_start = bend_start + bend_bits;
    static constexpr unsigned int fechip_start = strip_start + strip_bits;
    static constexpr unsigned int timestamp_start = fechip_start + fechip_bits;

    typedef sc_bv<bend_bits> bend_t;
    typedef sc_bv<strip_bits> strip_t;
    typedef sc_bv<fechip_bits> fechip_t;
    typedef sc_bv<timestamp_bits> timestamp_t;

    /** Constructor: All member variables are set to 0 by default. */
    stub_tfsb(const timestamp_t timestamp=0, const fechip_t fechip=0,
            const strip_t strip=0, const bend_t bend=0);

    /** Setter function for the timestamp */
    void set_timestamp(const timestamp_t timestamp);

    /** Getter function for the timestamp */
    timestamp_t  get_timestamp() const;

    /** Setter function for the front end chip number */
    void set_fechip(const fechip_t fechip);

    /** Getter function for the front end chip number */
    fechip_t  get_fechip() const;

    /** Setter function for the strip number */
    void set_strip(const strip_t strip);

    /** Getter function for the strip number */
    strip_t  get_strip() const;

    /** Setter function for the bend */
    void set_bend(const bend_t bend);

    /** Getter function for the bend */
    bend_t  get_bend() const;

    /** Getter function for the whole extended stub as a bit vector */
    sc_bv<total_width> get_bit_vector() const;

    /** Comparison of two stub objects */
    bool operator == (const stub_tfsb &rhs) const;

    /** Assignment operator for stubs */
    stub_tfsb& operator = (const stub_tfsb & rhs);

    /** Output function to print the address and bend of the extended stub. The
     * format is: [timestamp,fechip,strip,bend] */
    friend ostream& operator << <> (ostream &os, const stub_tfsb &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace <> (sc_trace_file *tf, const stub_tfsb &v,
            const std::string &name);

private:

    /** Timestamp represents the time when a hit happen within a time frame */
    timestamp_t timestamp;

    /** Front End Chip number from which the extended stub originates */
    fechip_t fechip;

    /** Strip number from which the extended stub originates */
    strip_t strip;

    /** Bend of the hit, representing the difference of the hits at the two
     * layers of one sensor. */
    bend_t bend;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
stub_tfsb<timestamp_bits, fechip_bits, strip_bits, bend_bits>::stub_tfsb(
        const timestamp_t timestamp, const fechip_t fechip, const strip_t strip,
        const bend_t bend) :
        timestamp(timestamp),
        fechip(fechip),
        strip(strip),
        bend(bend)
{
    return;
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline void stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::set_timestamp(const timestamp_t timestamp)
{
    this->timestamp = timestamp;

    return;
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline typename stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::timestamp_t stub_tfsb<timestamp_bits, fechip_bits,
        strip_bits, bend_bits>::get_timestamp() const
{
    return (timestamp);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline void stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::set_fechip(
        const fechip_t fechip)
{
    this->fechip = fechip;

    return;
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline typename stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::fechip_t stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::get_fechip() const
{
    return (fechip);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline void stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::set_strip(const strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline typename stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::strip_t stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::get_strip() const
{
  return (strip);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline void stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::set_bend(const bend_t bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
inline typename stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::bend_t stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::get_bend() const
{
    return (bend);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
sc_bv<stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::total_width> stub_tfsb<timestamp_bits, fechip_bits,
        strip_bits, bend_bits>::get_bit_vector() const
{
    sc_bv<total_width> full_stub;
    full_stub = ( (timestamp, fechip, strip, bend) );

    return (full_stub);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
bool stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::operator == (const stub_tfsb<timestamp_bits, fechip_bits,
        strip_bits, bend_bits> &rhs) const
{
    bool equality = true;
    equality = equality && (rhs.timestamp == timestamp);
    equality = equality && (rhs.fechip == fechip);
    equality = equality && (rhs.strip == strip);
    equality = equality && (rhs.bend == bend);

    return (equality);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
stub_tfsb<timestamp_bits, fechip_bits, strip_bits, bend_bits>&
        stub_tfsb<timestamp_bits, fechip_bits, strip_bits,
        bend_bits>::operator = (const stub_tfsb<timestamp_bits, fechip_bits,
        strip_bits, bend_bits> & rhs)
{
    timestamp = rhs.timestamp;
    fechip = rhs.fechip;
    strip = rhs.strip;
    bend = rhs.bend;

    return (*this);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
ostream& operator << (ostream &os, const stub_tfsb<timestamp_bits, fechip_bits,
        strip_bits, bend_bits> &v)
{
    os << "[" << std::hex
            << "T=" << v.timestamp.to_uint()
            << ",F=" << v.fechip.to_uint()
            << ",S=" << v.strip.to_uint()
            << ",B=" << v.bend.to_uint()
            << "]";

    return (os);
}

// *****************************************************************************
template<unsigned int timestamp_bits, unsigned int fechip_bits,
        unsigned int strip_bits, unsigned int bend_bits>
void sc_trace (sc_trace_file *tf, const stub_tfsb<timestamp_bits, fechip_bits,
        strip_bits, bend_bits> &v,
        const std::string &name)
{
    sc_trace(tf, v.timestamp, name + ".timestamp");
    sc_trace(tf, v.fechip, name + ".fechip");
    sc_trace(tf, v.strip, name + ".strip");
    sc_trace(tf, v.bend, name + ".bend");

    return;
}
