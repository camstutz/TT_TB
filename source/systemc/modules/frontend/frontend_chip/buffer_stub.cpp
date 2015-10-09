/* @file buffer_stub.cpp
 * @author Christian Amstutz
 * @date October 8, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "buffer_stub.hpp"

// *****************************************************************************
buffer_stub::buffer_stub() :
        stub(),
        buffer_bx(0)
{}

// *****************************************************************************
buffer_stub::buffer_stub(const buffer_bx_t buffer_bx, const stub& original_stub) :
        stub(original_stub),
        buffer_bx(buffer_bx)
{}

// *****************************************************************************
void buffer_stub::set_buffer_bx(const buffer_bx_t bx_buf)
{
    buffer_bx = bx_buf;

    return;
}

// *****************************************************************************
buffer_stub::buffer_bx_t buffer_stub::get_buffer_bx() const
{
    return buffer_bx;
}

// *****************************************************************************
bool buffer_stub::operator== (const buffer_stub& rhs) const
{
    bool equal = true;
    equal &= (configuration == rhs.configuration);
    equal &= (valid == rhs.get_valid());
    equal &= (bx == rhs.get_bx());
    equal &= (fechip == rhs.get_fechip());
    equal &= (strip == rhs.get_strip());
    equal &= (bend == rhs.get_bend());
    equal &= (pixel == rhs.get_pixel());
    equal &= (buffer_bx == rhs.buffer_bx);

    return equal;
}

// *****************************************************************************
buffer_stub& buffer_stub::operator= (const buffer_stub& rhs)
{
    configuration = rhs.configuration;

    set_valid(rhs.get_valid());
    set_bx(rhs.get_bx());
    set_fechip(rhs.get_fechip());
    set_strip(rhs.get_strip());
    set_bend(rhs.get_bend());
    set_pixel(rhs.get_pixel());
    set_buffer_bx(rhs.get_buffer_bx());

    return *this;
}

// *****************************************************************************
bool buffer_stub::operator< (const buffer_stub& rhs) const
{
    bool smaller = false;

    if (bend > rhs.get_bend())
    {
        smaller = true;
    }
    else if (bend == rhs.get_bend())
    {
        if (buffer_bx > rhs.get_buffer_bx())
        {
            smaller = true;
        }
        else if (buffer_bx == rhs.get_buffer_bx())
        {
            if (fechip > rhs.get_fechip())
            {
                smaller = true;
            }
            else if (fechip == rhs.get_fechip())
            {
                if (strip > rhs.get_strip())
                {
                    smaller = true;
                }
                else if (strip == rhs.get_strip())
                {
                    if (pixel > rhs.get_pixel())
                    {
                        smaller = true;
                    }
                    else if (pixel == rhs.get_pixel())
                    {

                    }
                }
            }
        }
    }

    return smaller;
}

