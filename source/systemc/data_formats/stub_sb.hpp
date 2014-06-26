/*!
 * @file stub_sb.hpp
 * @author Christian Amstutz
 * @date June 2, 2014
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

template <unsigned int strip_bits, unsigned int bend_bits>
class stub_sb;

template <unsigned int strip_bits, unsigned int bend_bits>
void sc_trace (sc_trace_file *tf, const stub_sb<strip_bits, bend_bits> &v,
        const std::string &name);

template <unsigned int strip_bits, unsigned int bend_bits>
ostream& operator << (ostream &os, stub_sb<strip_bits, bend_bits> const &v);

// *****************************************************************************

/*!
 * @brief Representation of a stub with the fields strip and bend
 */
template<unsigned int strip_bits, unsigned int bend_bits>
class stub_sb
{

public:
    static const unsigned int bend_width = bend_bits;
    static const unsigned int strip_width = strip_bits;
    static const unsigned int total_width = strip_bits + bend_bits;

    static const unsigned int bend_start = 0;
    static const unsigned int strip_start = bend_bits;

    typedef sc_bv<strip_bits> strip_t;
    typedef sc_bv<bend_bits> bend_t;

    /** Constructor. The default values are 0 for the address and 0 for the
     * bend. */
    stub_sb(const strip_t strip=0, const bend_t bend=0);

    /** Setter function for the strip address of the stub */
    void set_strip(const strip_t address);

    /** Getter function for the strip address of the stub */
    strip_t  get_strip() const;

    /** Setter function for the bend of the stub */
    void set_bend(const bend_t bend);

    /** Getter function for the address of the stub */
    bend_t  get_bend() const;

    /** Getter function for the whole stub as a bit vector */
    sc_bv<total_width> get_bit_vector() const;

    /** Comparison of two stub objects */
    bool operator == (const stub_sb &rhs) const;

    /** Assignment operator for stubs */
    stub_sb& operator = (const stub_sb & rhs);
    
    static size_t get_max_value_length();
    void get_string_value(char format_str, char* string_value);
    static void mti_debug_cb (void* var, char* mti_value, char format_str);

    /** Output function to print the address and bend of the stub. The format
     * is: [address,bend] */
    friend ostream& operator << <> (ostream &os, stub_sb const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace <> (sc_trace_file *tf, const stub_sb &v,
            const std::string &name);

private:
    /** Strip address of the strip on the silicon detector */
    strip_t strip;

    /** represents the distance of the hits between the two silicon detectors */
    bend_t bend;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
stub_sb<strip_bits, bend_bits>::stub_sb(const strip_t strip, const bend_t bend) :
        strip(strip),
        bend(bend)
{
  return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
inline void stub_sb<strip_bits, bend_bits>::set_strip(const strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
inline typename stub_sb<strip_bits, bend_bits>::strip_t
        stub_sb<strip_bits, bend_bits>::get_strip() const
{
    return (strip);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
inline void stub_sb<strip_bits, bend_bits>::set_bend(const bend_t bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
inline typename stub_sb<strip_bits, bend_bits>::bend_t
        stub_sb<strip_bits, bend_bits>::get_bend() const
{
    return (bend);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
inline sc_bv<stub_sb<strip_bits, bend_bits>::total_width>
        stub_sb<strip_bits, bend_bits>::get_bit_vector() const
{
    return ( (sc_bv<strip_width>(strip), sc_bv<bend_width>(bend)) );
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
inline bool stub_sb<strip_bits, bend_bits>::operator == (
        const stub_sb<strip_bits, bend_bits> &rhs) const
{
  return (rhs.strip == strip && rhs.bend == bend );
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
stub_sb<strip_bits, bend_bits>& stub_sb<strip_bits, bend_bits>::operator = (
        const stub_sb<strip_bits, bend_bits> & rhs)
{
    strip = rhs.strip;
    bend = rhs.bend;

    return (*this);
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
size_t stub_sb<strip_bits, bend_bits>::get_max_value_length()
{
    // todo: think about the return value of length
    return 20;
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
void stub_sb<strip_bits, bend_bits>::get_string_value(char format_str, char* string_value)
{
    std::stringstream my_string;
    //my_string << std::dec << strip << "," << bend;
    my_string << "test";
    std::strcpy (string_value, my_string.str().c_str());
    
    return;    
}

// *****************************************************************************
template<unsigned int strip_bits, unsigned int bend_bits>
void stub_sb<strip_bits, bend_bits>::mti_debug_cb (void* var, char* mti_value, char format_str)
{
    stub_sb<strip_bits, bend_bits>* typed_var = reinterpret_cast<stub_sb<strip_bits, bend_bits>* >(var);
    typed_var->get_string_value(format_str, mti_value);
    
    return;
}

// *****************************************************************************
template <unsigned int strip_bits, unsigned int bend_bits>
ostream& operator << (ostream &os, stub_sb<strip_bits, bend_bits> const &v)
{
    os << std::hex;
    os << "[S=" << v.strip.to_uint() << ",B=" << v.bend.to_uint() << "]";

    return (os);
}

// *****************************************************************************
template <unsigned int strip_bits, unsigned int bend_bits>
void sc_trace (sc_trace_file *tf, const stub_sb<strip_bits, bend_bits> &v,
        const std::string &name)
{
    sc_trace(tf, v.strip, name + ".strip");
    sc_trace(tf, v.bend, name + ".bend");

    return;
}
