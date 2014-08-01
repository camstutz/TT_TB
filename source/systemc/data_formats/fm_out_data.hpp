/*!
 * @fm_out_data.hpp
 * @author Christian Amstutz
 * @date July 31, 2014
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

// TODO: use template to configure?
#include "../systems/TT_configuration.hpp"
#include "stub_pzfs.hpp"

/*!
 * @brief
 */
class fm_out_data
{
public:
    typedef bool data_valid_flag_t;
    typedef bool time_stamp_flag_t;
    typedef stub_pzfs<DO_STUB_PHI_BITS, DO_STUB_Z_BITS, DO_STUB_FECHIP_BITS, DO_STUB_STRIP_BITS,
            DO_STUB_PHI_BITS+DO_STUB_Z_BITS+DO_STUB_FECHIP_BITS+DO_STUB_STRIP_BITS> fm_stub_t;
    typedef sc_bv<16> payload_t;
    typedef payload_t time_stamp_t;
    typedef sc_bv<18> data_t;

    static const unsigned int data_valid_pos = 17;
    static const unsigned int time_stamp_flag_pos = 16;

    /** Constructor: */
    fm_out_data();

    /** Constructor: */
    fm_out_data(const fm_stub_t stub_data);

    /** Constructor: */
    fm_out_data(const data_valid_flag_t data_valid, const fm_stub_t stub_data);

    /** Constructor: */
    fm_out_data(const time_stamp_t time_stamp);

    /** Setter function for the time_stamp */
    void set_data_valid_flag(const data_valid_flag_t new_data_valid);

    /** Setter function for the extended stub */
    void set_data_stub(const fm_stub_t new_stub);

    /** Setter function for the time_stamp */
    void set_data_time_stamp(const time_stamp_t new_time_stamp);

    data_valid_flag_t get_data_valid_flag() const;

    time_stamp_flag_t get_time_stamp_flag() const;

    data_t get_data() const;

    /** Getter function for the stub */
    fm_stub_t get_data_stub() const;

    /** Getter function for the time_stamp */
    time_stamp_t get_data_time_stamp() const;

    /** Comparison of two do_out_data objects */
    bool operator == (const fm_out_data &rhs) const;

    /** Assignment operator for fe_out_data */
    fm_out_data& operator = (const fm_out_data & rhs);

    static size_t get_max_value_length();
    void get_string_value(char format_str, char* string_value);

    /** Output function to print the data of the signal. The format is
     * [data_valid,timestamp_flag,[phi,z,fechip,superstrip]]
     */
    friend ostream& operator << (ostream &os, fm_out_data const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace(sc_trace_file *tf, const fm_out_data &v, const std::string &name);

    static void mti_debug_cb (void* var, char* mti_value, char format_str);

private:
    data_t data;

    /** Initializer function that is called by all the constructors that
     * generate stub data.#
     */
    void initialize_stub(const data_valid_flag_t data_valid, const fm_stub_t stub_data);

    /** Setter function for the data valid bit */
    void set_time_stamp_flag(const time_stamp_flag_t time_stamp_flag);
};
