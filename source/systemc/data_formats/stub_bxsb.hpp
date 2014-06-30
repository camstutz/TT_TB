/*!
 * @file stub_bxsb.hpp
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
#include <iostream>

#include <systemc.h>

#include "stub_sb.hpp"

// *****************************************************************************

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_bxsb;

template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
void sc_trace(sc_trace_file *tf,
        const stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits> &v,
        const std::string &name);

// *****************************************************************************

/*!
 * @brief
 */
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
class stub_bxsb : public stub_sb<strip_bits, bend_bits, total_bits>
{

public:
    static const unsigned int bx_width = bx_bits;

    static const unsigned int bend_start = 0;
    static const unsigned int strip_start = bend_start + bend_bits;
    static const unsigned int bx_start = strip_start + strip_bits;

    typedef stub_sb<strip_bits, bend_bits, total_bits> base;

    typedef unsigned int bx_t;
    typedef sc_bv<bx_bits> bv_bv_t;

    /** Constructor: All member variables are set to 0 by default. */
    stub_bxsb();
    stub_bxsb(const bx_t bx, const strip_t strip, const bend_t bend);
    virtual ~stub_bxsb();

    /** Setter function for the bunch crossing */
    void set_bx(const bx_t bx);

    /** Getter function for the bunch crossing */
    bx_t  get_bx() const;

    /** Comparison of two stub objects */
    bool operator== (const stub_bxsb& rhs) const;

    /** Assignment operator for stubs */
    stub_bxsb& operator= (const stub_bxsb& rhs);

protected:
    bool is_equal(const stub_bxsb& rhs);
    void copy(const stub_bxsb& original);

private:
    /** Bunch crossing (BX) represents the time when a hit happen within a time
     *  frame.
     */
    bx_t bx;

    /** Strip number from which the extended stub originates */
    strip_t strip;

    /** Bend of the hit, representing the difference of the hits at the two
     * layers of one sensor. */
    bend_t bend;
};

// *****************************************************************************

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::stub_bxsb() :
        stub_sb(0, 0)
{
    set_bx(0);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::stub_bxsb(
        const bx_t bx, const strip_t strip, const bend_t bend) :
        stub_sb(strip, bend)
{
    set_bx(bx);

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::set_bx(
        const bx_t bx)
{
    this->bx = bx;

    return;
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline typename stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::bx_t
        stub_bxsb<bx_bits, strip_bits, bend_bits,
        total_bits>::get_bx() const
{
    return (bx);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::operator== (
        const stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits> &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>&
        stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::operator= (
        const stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>& rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline bool stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::is_equal(
        const stub_bxsb& rhs)
{
    bool equal = false;
    equal = equal & (base::equal(rhs));
    equal = equal & (bx == rhs.get_bx());

    return (equal);
}

// *****************************************************************************
template<unsigned int bx_bits, unsigned int strip_bits, unsigned int bend_bits,
        unsigned int total_bits>
inline void stub_bxsb<bx_bits, strip_bits, bend_bits, total_bits>::copy(
        const stub_bxsb& original)
{
    base::copy(original);
    set_bx(original.get_bx());

    return;
}
