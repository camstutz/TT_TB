/*!
 * @dc_out_word.hpp
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
#include <iostream>

#include <systemc.h>

#include "../TT_configuration.hpp"
#include "stub_tfsb.hpp"

// *****************************************************************************

#define DC_OUT_WORD_WIDTH dc_out_word::dc_stub_t::total_width + 1

/*!
 * @brief
 */
class dc_out_word
{
public:
    typedef bool data_valid_t;
    typedef stub_tfsb<DC_WORD_TIME_BITS, DC_WORD_FE_BITS, FE_STUB_STRIP_BITS, FE_STUB_BEND_BITS> dc_stub_t;

    static const unsigned int width;

    /** Constructor: The default value for the data valid bit is set to false.
     *  */
    dc_out_word(data_valid_t dv = false);

    /** Constructor: The default value for the data valid bit is set to false.
     *  */
    dc_out_word(data_valid_t dv, dc_stub_t data);

    /** Setter function for the data valid bit */
    void set_dv(const data_valid_t dv_bit);

    /** Getter function for the data valid bit */
    data_valid_t get_dv() const;

    /** Setter function for the extended stub */
    void set_data(const dc_stub_t new_stub);

    /** Getter function for the extended stub */
    dc_stub_t get_data() const;

    /** Getter function for the whole dc_out_word as a bit vector */
    sc_bv<DC_OUT_WORD_WIDTH> get_bit_vector() const;

    /** Comparison of two dc_out_word objects */
    bool operator == (const dc_out_word &rhs) const;

    /** Assignment operator for dc_out_word */
    dc_out_word& operator = (const dc_out_word & rhs);
    
    static size_t get_max_value_length();
    void get_string_value(char format_str, char* string_value);
    static void mti_debug_cb (void* var, char* mti_value, char format_str);    

    /** Output function to print the data of the signal. The format is
     * [dv,[T=time,F=fechip,S=strip,B=bend]] */
    friend ostream& operator << (ostream &os, dc_out_word const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace(sc_trace_file *tf, const dc_out_word &v, const std::string &name);

private:
    /** A bit that show if the data is valid in the actual clock cycle */
    data_valid_t dv;

    /** contains an extended stub */
    dc_stub_t data;
};
