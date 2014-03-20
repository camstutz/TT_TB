/*!
 * @fe_out_data.hpp
 * @author Christian Amstutz
 * @date Mar 18, 2014
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
#include "stub_sb.hpp"

/*!
 * @brief Representation of the front end chip output data
 */
class fe_out_data
{
public:
    typedef bool data_valid_t;
    typedef stub_sb<FE_STUB_STRIP_BITS, FE_STUB_BEND_BITS> fe_stub_t;

    /** Constructor. The default value for the data valid bit is set to false.
     *  */
    fe_out_data();

    /** Setter function for the data valid bit */
    void set_dv(const data_valid_t dv_bit);

    /** Getter function for the data valid bit */
    data_valid_t get_dv() const;

    /** Setter function for the  stub */
    void set_data(const fe_stub_t new_stub);

    /** Getter function for the stub */
    fe_stub_t get_data() const;

    /** Comparison of two fe_out_data objects */
    bool operator == (const fe_out_data &rhs) const;

    /** Assignment operator for fe_out_data */
    fe_out_data& operator = (const fe_out_data & rhs);

    /** Output function to print the data of the signal. The format is
     * [dv,[address,bend]] */
    friend ostream& operator << (ostream &os, fe_out_data const &v);

    /** Function for tracing support in SystemC */
    friend void sc_trace(sc_trace_file *tf, const fe_out_data &v, const std::string &name);

private:
    /** A bit that show if the data is valid in the actual clock cycle */
    data_valid_t dv;

    /** contains a stub */
    fe_stub_t data;
};
