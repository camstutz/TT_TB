/*!
 * @file stub.cpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub.hpp"

// *****************************************************************************
stub::stub()
{
    this->valid = 0;
    this->bx = 0;
    this->fechip = 0;
    this->strip = 0;
    this->bend = 0;
    this->pixel = 0;

    return;
}

// *****************************************************************************
stub::stub(stub_config configuration) :
                configuration(configuration)
{
    this->valid = 0;
    this->bx = 0;
    this->fechip = 0;
    this->strip = 0;
    this->bend = 0;
    this->pixel = 0;

    return;
}

// *****************************************************************************
stub::stub(stub_config configuration, const valid_t valid, const bx_t bx,
        const fechip_t fechip, const strip_t strip, const bend_t bend,
        const pixel_t pixel) :
        configuration(configuration)
{
    set_valid(valid);
    set_bx(bx);
    set_fechip(fechip);
    set_strip(strip);
    set_bend(bend);
    set_pixel(pixel);

    return;
}

// *****************************************************************************
void stub::set_valid(const valid_t valid)
{
    this->valid = valid;

    return;
}

// *****************************************************************************
stub::valid_t stub::get_valid() const
{
    return valid;
}

// *****************************************************************************
void stub::set_bx(const bx_t bx)
{
    this->bx = bx;

    return;
}

// *****************************************************************************
stub::bx_t stub::get_bx() const
{
    return bx;
}

// *****************************************************************************
void stub::set_fechip(const fechip_t fechip)
{
    this->fechip = fechip;

    return;
}

// *****************************************************************************
stub::fechip_t stub::get_fechip() const
{
    return fechip;
}

// *****************************************************************************
void stub::set_strip(const strip_t strip)
{
    this->strip = strip;

    return;
}

// *****************************************************************************
stub::strip_t stub::get_strip() const
{
    return strip;
}

// *****************************************************************************
void stub::set_bend(const bend_t bend)
{
    this->bend = bend;

    return;
}

// *****************************************************************************
stub::bend_t stub::get_bend() const
{
    return bend;
}

// *****************************************************************************
void stub::set_pixel(const pixel_t pixel)
{
    this->pixel = pixel;

    return;
}

// *****************************************************************************
stub::pixel_t stub::get_pixel() const
{
    return pixel;
}

//// *****************************************************************************
//typename stub_vbxpfsb<bx_bits, pixel_bits, fechip_bits, strip_bits, bend_bits,
//        total_bits>::full_bv_t stub_vbxpfsb<bx_bits, pixel_bits, fechip_bits,
//        strip_bits, bend_bits, total_bits>::get_bitvector() const
//{
//    full_bv_t output_bv;
//
//    output_bv(valid_start+valid_width-1, valid_start) = this->get_valid();
//    output_bv(bx_start+base::bx_width-1, bx_start) = this->get_bx();
//    output_bv(pixel_start+base::pixel_width-1, pixel_start) = this->get_pixel();
//    output_bv(fechip_start+fechip_width-1, fechip_start) = this->get_fechip();
//    output_bv(strip_start+base::strip_width-1, strip_start) = this->get_strip();
//    output_bv(bend_start+base::bend_width-1, bend_start) = this->get_bend();
//
//    return (output_bv);
//}
//
//// *****************************************************************************
//void stub_vbxpfsb<bx_bits, pixel_bits, fechip_bits, strip_bits, bend_bits,
//        total_bits>::set_bitvector(full_bv_t bit_vector)
//{
//  this->set_valid(bit_vector(valid_start+valid_width-1, valid_start).to_uint());
//    this->set_bx(bit_vector(bx_start+base::bx_width-1, bx_start).to_uint());
//    this->set_pixel(bit_vector(pixel_start+base::pixel_width-1, pixel_start).to_uint());
//    this->set_fechip(bit_vector(fechip_start+fechip_width-1, fechip_start).to_uint());
//    this->set_strip(bit_vector(strip_start+base::strip_width-1, strip_start).to_uint());
//    this->set_bend(bit_vector(bend_start+base::bend_width-1, bend_start).to_uint());
//
//    return;
//}

//// *****************************************************************************
//inline size_t stub_vbxpfsb<bx_bits, pixel_bits, fechip_bits, strip_bits,
//        bend_bits, total_bits>::get_max_string_length() const
//{
//    // todo: relative to widths of fields
//    return (21);
//}

// *****************************************************************************
std::string stub::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "V="  << this->get_valid()
                      << "BX=" << this->get_bx()
                      << "F="  << this->get_fechip()
                      << "S="  << this->get_strip()
                      << "B="  << this->get_bend()
                      << "P="  << this->get_pixel() << "]";

    return out_string.str();
}

// *****************************************************************************
bool stub::operator== (const stub& rhs) const
{
    bool equal = false;
    equal &= (configuration == rhs.configuration);
    equal &= (valid == rhs.get_valid());
    equal &= (bx == rhs.get_bx());
    equal &= (fechip == rhs.get_fechip());
    equal &= (strip == rhs.get_strip());
    equal &= (bend == rhs.get_bend());
    equal &= (pixel == rhs.get_pixel());

    return equal;
}

// *****************************************************************************
stub& stub::operator= (const stub& rhs)
{
    configuration = rhs.configuration;

    set_valid(rhs.get_valid());
    set_bx(rhs.get_bx());
    set_fechip(rhs.get_fechip());
    set_strip(rhs.get_strip());
    set_bend(rhs.get_bend());
    set_pixel(rhs.get_pixel());

    return *this;
}

// *****************************************************************************
ostream& operator<< (ostream &os, stub const &v)
{
    os << "v=" << v.valid;
    os << "bx=" << v.bx;
    os << "fe=" << v.fechip;
    os << "s=" << v.strip;
    os << "b=" << v.bend;
    os << "p=" << v.pixel;

    return os;
};

// *****************************************************************************
void sc_trace (sc_trace_file *tf, const stub &v,
        const std::string &name)
{
    sc_trace(tf, v.valid, name + ".valid");
    sc_trace(tf, v.bx, name + ".bx");
    sc_trace(tf, v.fechip, name + ".fechip");
    sc_trace(tf, v.strip, name + ".strip");
    sc_trace(tf, v.bend, name + ".bend");
    sc_trace(tf, v.pixel, name + ".pixel");

    return;
}
