/*!
 * @file do_out_data.cpp
 * @author Christian Amstutz
 * @date Mar 18, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "do_out_data.hpp"

// *****************************************************************************
do_out_data::do_out_data(data_valid_t dv) :
    dv(dv)
{
    data = do_stub_t();

    return;
}

// *****************************************************************************
do_out_data::do_out_data(data_valid_t dv, do_stub_t data) :
        dv(dv),
        data(data)
{
    return;
}

// *****************************************************************************
void do_out_data::set_dv(const data_valid_t dv_bit)
{
    dv = dv_bit;

    return;
}

// *****************************************************************************
do_out_data::data_valid_t do_out_data::get_dv() const
{
    return (dv);
}

// *****************************************************************************
void do_out_data::set_data(const do_stub_t data)
{
    this->data = data;

    return;
}

// *****************************************************************************
do_out_data::do_stub_t do_out_data::get_data() const
{
    return (data);
}

// *****************************************************************************
bool do_out_data::operator == (const do_out_data &rhs) const
{
  return (rhs.dv == dv && rhs.data == data );
}

// *****************************************************************************
do_out_data& do_out_data::operator = (const do_out_data& rhs)
{
    dv = rhs.dv;
    data = rhs.data;

    return (*this);
}

// *****************************************************************************
ostream& operator << (ostream &os, do_out_data const &v)
{
  os << "[" << v.dv << v.data << "]";

  return (os);
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const do_out_data &v, const std::string &name)
{
  sc_trace(tf, v.dv, name + ".dv");
  sc_trace(tf, v.data, name + ".data");

  return;
}