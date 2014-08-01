/*!
 * @fm_out_data.hpp
 * @author Christian Amstutz
 * @date Aug 1, 2014
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
#include "multifield_base.hpp"
#include "../modules/backend/data_organizer/data_organizer_one_layer.hpp"

// *****************************************************************************

/*!
 * @brief
 */
class fm_out_data : public multifield_base<data_organizer_one_layer::do_stub_t::total_width+1>
{
public:
    typedef multifield_base<data_organizer_one_layer::do_stub_t::total_width+1> base;

    typedef data_organizer_one_layer::do_stub_t fm_stub_t;
    typedef fm_stub_t::full_bv_t fm_stub_bv_t;
    typedef unsigned int payload_t;
    typedef fm_stub_bv_t payload_bv_t;
    typedef payload_t timestamp_t;
    typedef fm_stub_bv_t timestamp_bv_t;
    typedef bool timestamp_flag_t;
    typedef typename base::full_bv_t full_bv_t;

    static const unsigned int payload_width = data_organizer_one_layer::do_stub_t::total_width;
    static const unsigned int fm_stub_width = payload_width;
    static const unsigned int timestamp_width = payload_width;
    static const unsigned int timestamp_flag_width = 1;

    static const unsigned int payload_start = 0;
    static const unsigned int fm_stub_start = payload_start;
    static const unsigned int timestamp_start = payload_start;
    static const unsigned int timestamp_flag_start = payload_start + payload_width;

    static const bool TIMESTAMP = true;
    static const bool STUB = false;

    /** Constructor: */
    fm_out_data(const fm_stub_t stub_data = fm_stub_t());

    /** Constructor: */
    fm_out_data(const timestamp_t timestamp);

    virtual ~fm_out_data();

    /** Setter function for the extended stub */
    void set_data_stub(const fm_stub_t new_stub);

    /** Getter function for the stub */
    fm_stub_t get_data_stub() const;

    /** Setter function for the time_stamp */
    void set_timestamp(const timestamp_t new_time_stamp);

    /** Getter function for the time_stamp */
    timestamp_t get_timestamp() const;

    timestamp_flag_t is_timestamp() const;

    virtual full_bv_t get_bitvector() const;
    virtual void set_bitvector(full_bv_t bit_vector);

    virtual size_t get_max_string_length() const;
    virtual std::string get_string() const;

    /** Comparison of two stub objects */
    bool operator== (const fm_out_data &rhs) const;

    /** Assignment operator for stubs */
    fm_out_data& operator= (const fm_out_data & rhs);

protected:
    bool is_equal(const fm_out_data& rhs) const;
    void copy(const fm_out_data& original);

private:
    timestamp_flag_t timestamp_flag;
    payload_t payload;

/** Function for tracing support in SystemC */
friend void sc_trace (sc_trace_file *tf, const fm_out_data &v,
            const std::string &name);
};
