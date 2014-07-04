/*!
 * @file dc_out_word.hpp
 * @author Christian Amstutz
 * @date July 3, 2014
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

template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
class dc_out_word;

template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const dc_out_word<header_bits, payload_bits,
        total_bits> &v, const std::string &name);

// *****************************************************************************

/*!
 * @brief Representation of a stub with the fields strip and bend
 */
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
class dc_out_word : public multifield_base<total_bits>
{

public:
    typedef multifield_base<total_bits> base;

    typedef unsigned int header_t;
    typedef sc_bv<header_bits> header_bv_t;
    typedef unsigned int payload_t;
    typedef sc_bv<payload_bits> payload_bv_t;
    typedef typename base::full_bv_t full_bv_t;

    static const unsigned int header_width = header_bits;
    static const unsigned int payload_width = payload_bits;

    static const unsigned int payload_start = 0;
    static const unsigned int header_start = payload_bits;

    dc_out_word();
    dc_out_word(const header_t header, const payload_t payload);
    virtual ~dc_out_word();

    void set_header(const header_t header);
    header_t get_header() const;
    void set_payload(const payload_t payload);
    payload_t get_payload() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length() const;
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const dc_out_word &rhs) const;

    /** Assignment operator for stubs */
    dc_out_word& operator= (const dc_out_word & rhs);

protected:
    bool is_equal(const dc_out_word& rhs);
    void copy(const dc_out_word& original);

private:
    header_t header;
    payload_t payload;

/** Function for tracing support in SystemC */
friend void sc_trace <> (sc_trace_file *tf, const dc_out_word &v,
            const std::string &name);
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
dc_out_word<header_bits, payload_bits, total_bits>::dc_out_word() :
        header(0),
        payload(0)
{
  return;
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
dc_out_word<header_bits, payload_bits, total_bits>::dc_out_word(
        const header_t header, const payload_t payload)
{
    set_header(header);
    set_payload(payload);

    return;
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
dc_out_word<header_bits, payload_bits, total_bits>::~dc_out_word()
{}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline void dc_out_word<header_bits, payload_bits, total_bits>::set_header(
        const header_t header)
{
    // todo: check range
    this->header = header;

    return;
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline typename dc_out_word<header_bits, payload_bits, total_bits>::header_t
        dc_out_word<header_bits, payload_bits, total_bits>::get_header() const
{
    return (header);
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline void dc_out_word<header_bits, payload_bits, total_bits>::set_payload(
        const payload_t payload)
{
    // todo: check range
    this->payload = payload;

    return;
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline typename dc_out_word<header_bits, payload_bits, total_bits>::payload_t
        dc_out_word<header_bits, payload_bits, total_bits>::get_payload() const
{
    return (payload);
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
typename dc_out_word<header_bits, payload_bits, total_bits>::full_bv_t
        dc_out_word<header_bits, payload_bits, total_bits>::get_bitvector() const
{
    return ( (header_bv_t(header), payload_bv_t(payload) ) );
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
void dc_out_word<header_bits, payload_bits, total_bits>::set_bitvector(
        full_bv_t bit_vector)
{
    set_header(bit_vector(header_start, header_start+header_width-1).to_uint());
    set_payload(bit_vector(payload_start, payload_start+payload_width-1).to_uint());

    return;
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline size_t dc_out_word<header_bits, payload_bits,
        total_bits>::get_max_string_length() const
{
    // todo: Is there an intelligent way to determine max length of string?
    return (25);
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
std::string dc_out_word<header_bits, payload_bits, total_bits>::get_string()
        const
{
    std::stringstream out_string;
    out_string << "[" << "H=" << header
                      << "P=" << payload << "]";

    return (out_string.str());
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline bool dc_out_word<header_bits, payload_bits, total_bits>::operator== (
        const dc_out_word<header_bits, payload_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline dc_out_word<header_bits, payload_bits, total_bits>&
        dc_out_word<header_bits, payload_bits, total_bits>::operator= (
        const dc_out_word<header_bits, payload_bits, total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline bool dc_out_word<header_bits, payload_bits, total_bits>::is_equal(
        const dc_out_word& rhs)
{
    return (rhs.get_header() == header && rhs.get_payload() == payload);
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
inline void dc_out_word<header_bits, payload_bits, total_bits>::copy(
        const dc_out_word& original)
{
    set_header(original.get_header());
    set_payload(original.get_payload());

    return;
}

// *****************************************************************************
template<unsigned int header_bits, unsigned int payload_bits,
        unsigned int total_bits>
void sc_trace (sc_trace_file *tf, const dc_out_word<header_bits, payload_bits,
        total_bits> &v, const std::string &name)
{
    sc_trace(tf, v.get_header(), name + ".header");
    sc_trace(tf, v.get_payload(), name + ".payload");

    return;
}
