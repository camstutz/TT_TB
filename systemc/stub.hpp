/*!
 * @file stub.hpp
 * @author Christian Amstutz
 * @date Mar 17, 2014
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

#include "TT_configuration.hpp"

/*!
 * @brief
 */
class stub
{
public:
    typedef sc_bv<NR_STUB_ADDRESS_BITS> stub_address_t;
    typedef sc_bv<NR_STUB_BEND_BITS> stub_bend_t;

    /** Constructor. The default values are 0 for the address and 0 for the
     * bend. */
    stub(const stub_address_t address=0, const stub_bend_t bend=0);

    /** Setter function for the address of the stub */
    void setAddress(const stub_address_t address);

    /** Getter function for the address of the stub */
    stub_address_t  getAddress() const;

    /** Setter function for the bend of the stub */
    void setBend(const stub_bend_t bend);

    /** Getter function for the address of the stub */
    stub_bend_t  getBend() const;

    /** Getter function for the whole stub as a bit vector */
    sc_bv<NR_STUB_ADDRESS_BITS + NR_STUB_BEND_BITS> getBitVector() const;

    /** Comparison of two stub objects */
    bool operator == (const stub &rhs) const;

    /** Assignment operator for stubs */
    stub& operator = (const stub & rhs);

    /** Output function to print the address and bend of the stub. The format is
     * [address,bend] */
    friend ostream& operator << (ostream &os, stub const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace(sc_trace_file *tf, const stub &v,
            const std::string &name);

private:
    /** Address of the strip on the silicon detector */
    stub_address_t address;

    /** represents the difference of the hits between the two silicon detectors
     * */
    stub_bend_t bend;
};
