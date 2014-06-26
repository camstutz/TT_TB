/*!
 * @do_out_data.hpp
 * @author Christian Amstutz
 * @date June 4, 2014
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

#include "../systems/TT_configuration.hpp"
#include "stub_pzfs.hpp"

/*!
 * @brief
 */
class do_out_data
{
public:
    typedef bool data_valid_t;
    typedef stub_pzfs<DO_STUB_PHI_BITS, DO_STUB_Z_BITS, DO_STUB_FECHIP_BITS, DO_STUB_STRIP_BITS> do_stub_t;

    /** Constructor: The default value for the data valid bit is set to false.
     *  */
    do_out_data(data_valid_t dv = false);

    /** Constructor: The default value for the data valid bit is set to false.
     *  */
    do_out_data(data_valid_t dv, do_stub_t data);

    /** Setter function for the data valid bit */
    void set_dv(const data_valid_t dv_bit);

    /** Getter function for the data valid bit */
    data_valid_t get_dv() const;

    /** Setter function for the extended stub */
    void set_data(const do_stub_t new_stub);

    /** Getter function for the extended stub */
    do_stub_t get_data() const;

    /** Comparison of two do_out_data objects */
    bool operator == (const do_out_data &rhs) const;

    /** Assignment operator for fe_out_data */
    do_out_data& operator = (const do_out_data & rhs);

    static size_t get_max_value_length();
    void get_string_value(char format_str, char* string_value);

    /** Output function to print the data of the signal. The format is
     * [dv,[phi,z,fechip,strip]] */
    friend ostream& operator << (ostream &os, do_out_data const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace(sc_trace_file *tf, const do_out_data &v, const std::string &name);

    static void mti_debug_cb (void* var, char* mti_value, char format_str);

private:
    /** A bit that show if the data is valid in the actual clock cycle */
    data_valid_t dv;

    /** contains an extended stub */
    do_stub_t data;
};
