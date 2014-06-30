/*!
 * @file stub_sb.hpp
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

#include "multifield_base.hpp"

// *****************************************************************************

template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_sb;

template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_sb<strip_bits, bend_bits,
        total_bits> &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief Representation of a stub with the fields strip and bend
 */
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_sb : public multifield_base<total_bits>
{

public:
    static const unsigned int bend_width = bend_bits;
    static const unsigned int strip_width = strip_bits;

    static const unsigned int bend_start = 0;
    static const unsigned int strip_start = bend_bits;

    typedef multifield_base<total_bits> base;

    typedef unsigned int strip_t;
    typedef sc_bv<strip_bits> strip_bv_t;
    typedef unsigned int bend_t;
    typedef sc_bv<strip_bits> bend_bv_t;
    typedef typename base::full_bv_t full_bv_t;

    stub_sb();
    stub_sb(const strip_t strip, const bend_t bend);
    virtual ~stub_sb();

    void set_strip(const strip_t strip);
    strip_t get_strip() const;
    void set_bend(const bend_t bend);
    strip_t get_bend() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    /** Comparison of two stub objects */
    bool operator== (const stub_sb &rhs) const;

    /** Assignment operator for stubs */
    stub_sb& operator= (const stub_sb & rhs);
    
    virtual size_t get_max_string_length();
    virtual std::string get_string() const;

protected:
    bool is_equal(const stub_sb& rhs);
    void copy(const stub_sb& original);

private:
    /** Strip address of the strip on the silicon detector */
    strip_t strip;

    /** represents the distance of the hits between the two silicon detectors */
    bend_t bend;

    /** Function for tracing support in SystemC */
    friend void sc_trace <> (sc_trace_file *tf, const stub_sb &v,
            const std::string &name);
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_sb<strip_bits, bend_bits, total_bits>::stub_sb() :
        strip(0),
        bend(0)
{
  return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_sb<strip_bits, bend_bits, total_bits>::stub_sb(const strip_t strip,
        const bend_t bend)
{
    set_strip(strip);
    set_bend(bend);

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_sb<strip_bits, bend_bits, total_bits>::set_strip(
        const strip_t strip)
{
    // todo: check range
    this->strip = strip;

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline typename stub_sb<strip_bits, bend_bits, total_bits>::strip_t
        stub_sb<strip_bits, bend_bits, total_bits>::get_strip() const
{
    return (strip);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_sb<strip_bits, bend_bits, total_bits>::set_bend(
        const bend_t bend)
{
    // todo: check range
    this->bend = bend;

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline typename stub_sb<strip_bits, bend_bits, total_bits>::bend_t
        stub_sb<strip_bits, bend_bits, total_bits>::get_bend() const
{
    return (bend);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
typename stub_sb<strip_bits, bend_bits, total_bits>::full_bv_t
        stub_sb<strip_bits, bend_bits, total_bits>::get_bitvector() const
{
    return ( (strip_bv_t(strip), bend_bv_t(bend) ) );
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void stub_sb<strip_bits, bend_bits, total_bits>::set_bitvector(
        full_bv_t bit_vector)
{
    set_strip(bit_vector(strip_start, strip_start+strip_width-1));
    set_bend(bit_vector(bend_start, bend_start+bend_width-1));

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_sb<strip_bits, bend_bits, total_bits>::operator== (
        const stub_sb<strip_bits, bend_bits, total_bits> &rhs) const
{
  return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline stub_sb<strip_bits, bend_bits, total_bits>&
        stub_sb<strip_bits, bend_bits, total_bits>::operator= (
        const stub_sb<strip_bits, bend_bits, total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline size_t stub_sb<strip_bits, bend_bits, total_bits>::get_max_string_length()
{
    // todo: Is there an intelligent way to determine max length of string?
    return (13);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
std::string stub_sb<strip_bits, bend_bits, total_bits>::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "S=" << strip << "B=" << bend << "]";
    
    return (out_string);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_sb<strip_bits, bend_bits, total_bits>::is_equal(
        const stub_sb& rhs)
{
    return (rhs.get_strip() == strip && rhs.get_bend() == bend);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_sb<strip_bits, bend_bits, total_bits>::copy(
        const stub_sb& original)
{
    set_strip(original.get_strip());
    set_bend(original.get_bend());

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const stub_sb<strip_bits, bend_bits,
        total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.get_strip(), name + ".strip");
    sc_trace(tf, v.get_bend(), name + ".bend");

    return;
}
