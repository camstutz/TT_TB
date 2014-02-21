/*!
 * @do_out_data.hpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
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

#include "stub_ext.hpp"

/*!
 * @brief
 */
class do_out_data
{
public:
    typedef bool data_valid_t;

    /** Constructor. The default value for the data valid bit is set to false.
     *  */
    do_out_data();

    /** Setter function for the data valid bit */
    void set_dv(const data_valid_t dv_bit);

    /** Getter function for the data valid bit */
    data_valid_t get_dv() const;

    /** Setter function for the extended stub */
    void set_data(const stub_ext new_stub);

    /** Getter function for the extended stub */
    stub_ext get_data() const;

    /** Comparison of two do_out_data objects */
    bool operator == (const do_out_data &rhs) const;

    /** Assignment operator for fe_out_data */
    do_out_data& operator = (const do_out_data & rhs);

    /** Output function to print the data of the signal. The format is
     * [dv,[phi,z,fechip,strip]] */
    friend ostream& operator << (ostream &os, do_out_data const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace(sc_trace_file *tf, const do_out_data &v, const std::string &name);

private:
    /** A bit that show if the data is valid in the actual clock cycle */
    data_valid_t dv;

    /** contains an extended stub */
    stub_ext data;
};
