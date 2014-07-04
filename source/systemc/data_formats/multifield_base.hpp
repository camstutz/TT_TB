/*!
 * @file multifield_base.hpp
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
#include <iostream>

#include <systemc.h>

// *****************************************************************************

template <unsigned int total_bits>
class multifield_base;

template <unsigned int total_bits>
ostream& operator<< (ostream &os, multifield_base<total_bits> const &v);

// *****************************************************************************

template <unsigned int total_bits>
class multifield_base
{
public:
    static const unsigned int total_width = total_bits;

    typedef sc_bv<total_width> full_bv_t;

    virtual ~multifield_base();

    virtual full_bv_t get_bitvector() const =0;
    virtual void set_bitvector(full_bv_t bit_vector) =0;

    virtual size_t get_max_string_length() const =0;
    virtual std::string get_string() const =0;
    virtual void get_string(char format_str, char* string_value) const;

    virtual void mti_debug_cb (void* var, char* mti_value, char format_str);

    // todo: check if this friend/template stuff is correct
    friend ostream& operator<< <> (ostream &os, multifield_base<total_bits> const &v);
};

// *****************************************************************************

// *****************************************************************************
template <unsigned int total_bits>
multifield_base<total_bits>::~multifield_base()
{}

// *****************************************************************************
template <unsigned int total_bits>
void multifield_base<total_bits>::get_string(char format_str, char* string_value) const
{
    std::strcpy(string_value, get_string().c_str());
    return;
}

// *****************************************************************************
template <unsigned int total_bits>
void multifield_base<total_bits>::mti_debug_cb (void* var, char* mti_value, char format_str)
{
    //stub_sb<strip_bits, bend_bits>* typed_var = reinterpret_cast<stub_sb<strip_bits, bend_bits>* >(var);
    this->get_string(format_str, mti_value);

    return;
}

// *****************************************************************************
template <unsigned int total_bits>
ostream& operator<< (ostream &os, multifield_base<total_bits> const &v)
{
    os << v.get_string();
    return (os);
}
