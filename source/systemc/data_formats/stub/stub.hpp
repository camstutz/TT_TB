/*!
 * @file stub.hpp
 * @author Christian Amstutz
 * @date July 30, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "stub_config.hpp"

#include <string>
#include <sstream>
#include <iostream>

#include <systemc.h>

// *****************************************************************************

/*!
 * @brief
 */
class stub
{

public:
    typedef bool valid_t;
    typedef unsigned int bx_t;
    typedef unsigned int fechip_t;
    typedef unsigned int strip_t;
    typedef int bend_t;
    typedef unsigned int pixel_t;

    stub_config configuration;

    /** Constructor: All member variables are set to 0 by default. */
    stub();
    stub(stub_config configuration);
    stub(stub_config configuration, const valid_t valid, const bx_t bx,
            const fechip_t fechip, const strip_t strip, const bend_t bend,
            const pixel_t pixel);

    /** Setter function for the data valid bit */
    void set_valid(const valid_t valid);

    /** Getter function for the data valid bit */
    valid_t get_valid() const;

    void set_bx(const bx_t bx);
    bx_t get_bx() const;

    /** Setter function for the front end chip number */
    void set_fechip(const fechip_t fechip);

    /** Getter function for the front end chip number */
    fechip_t  get_fechip() const;

    void set_strip(const strip_t strip);
    strip_t get_strip() const;
    void set_bend(const bend_t bend);
    bend_t get_bend() const;
    void set_pixel(const pixel_t pixel);
    pixel_t get_pixel() const;

//    virtual full_bv_t get_bitvector() const;
//    virtual void set_bitvector(full_bv_t bit_vector);

//    size_t get_max_string_length() const;
    std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const stub& rhs) const;

    /** Assignment operator for stubs */
    stub& operator= (const stub& rhs);

protected:
    /** Data valid bit for the stub */
    valid_t valid;

    /** Bunch crossing (BX) represents the time when a hit happen within a time
     *  frame.
     */
    bx_t bx;

    /** Front end chip number, indicating the FE chip on one side of a sensor
     *  module.
     */
    fechip_t fechip;

    /** Strip address of the strip on the silicon detector */
    strip_t strip;

    /** represents the distance of the hits between the two silicon detectors */
    bend_t bend;

    /** Front end chip number, indicating the FE chip on one side of a sensor
     *  module.
     */
    pixel_t pixel;

    friend ostream& operator<< (ostream &os, stub const &v);
    friend void sc_trace (sc_trace_file *tf, const stub &v, const std::string &name);
};
