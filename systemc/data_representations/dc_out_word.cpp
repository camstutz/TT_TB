/*!
 * @file do_out_data.cpp
 * @author Christian Amstutz
 * @date May 19, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "dc_out_word.hpp"

// *****************************************************************************
const unsigned int dc_out_word::width = DC_OUT_WORD_WIDTH;

// *****************************************************************************
dc_out_word::dc_out_word(data_valid_t dv) :
    dv(dv)
{
    data = dc_stub_t();

    return;
}

// *****************************************************************************
dc_out_word::dc_out_word(data_valid_t dv, dc_stub_t data) :
        dv(dv),
        data(data)
{
    return;
}

// *****************************************************************************
void dc_out_word::set_dv(const data_valid_t dv_bit)
{
    dv = dv_bit;

    return;
}

// *****************************************************************************
dc_out_word::data_valid_t dc_out_word::get_dv() const
{
    return (dv);
}

// *****************************************************************************
void dc_out_word::set_data(const dc_stub_t data)
{
    this->data = data;

    return;
}

// *****************************************************************************
dc_out_word::dc_stub_t dc_out_word::get_data() const
{
    return (data);
}

// *****************************************************************************
sc_bv<DC_OUT_WORD_WIDTH> dc_out_word::get_bit_vector() const
{
    return ( ( (get_dv(), get_data().get_bit_vector()) ) );
}

// *****************************************************************************
bool dc_out_word::operator == (const dc_out_word &rhs) const
{
  return (rhs.dv == dv && rhs.data == data );
}

// *****************************************************************************
dc_out_word& dc_out_word::operator = (const dc_out_word& rhs)
{
    dv = rhs.dv;
    data = rhs.data;

    return (*this);
}

// *****************************************************************************
ostream& operator << (ostream &os, dc_out_word const &v)
{
  os << "[" << v.dv << v.data << "]";

  return (os);
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const dc_out_word &v, const std::string &name)
{
  sc_trace(tf, v.dv, name + ".dv");
  sc_trace(tf, v.data, name + ".data");

  return;
}
