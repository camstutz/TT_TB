/* @file buffer_stub.hpp
 * @author Christian Amstutz
 * @date October 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/stub/stub.hpp"
#include "../../../data_formats/stub/stub_config.hpp"

// *****************************************************************************

/*!
 * @brief
 */
class buffer_stub : public stub
{

public:
    typedef unsigned int buffer_bx_t;

    /** Constructor: All member variables are set to 0 by default. */
    buffer_stub();
    buffer_stub(const buffer_bx_t buffer_bx, const stub& stub);

    void set_buffer_bx(const buffer_bx_t bx_buf);
    buffer_bx_t get_buffer_bx() const;

    /** Comparison of two stub objects */
    bool operator== (const buffer_stub& rhs) const;

    /** Assignment operator for stubs */
    buffer_stub& operator= (const buffer_stub& rhs);

    /** Comparison of two stub objects */
    bool operator< (const buffer_stub& rhs) const;

protected:
    buffer_bx_t buffer_bx;
};
