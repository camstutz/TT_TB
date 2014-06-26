/*!
 * @file do_out_data.cpp
 * @author Christian Amstutz
 * @date June 4, 2014
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
size_t do_out_data::get_max_value_length()
{
    // todo: think about the return value of length
    return 20;
}

// *****************************************************************************
void do_out_data::get_string_value(char format_str, char* string_value)
{
    std::stringstream my_string;
    my_string <<  dv << "," << data;
    std::strcpy (string_value, my_string.str().c_str());

    return;
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

// *****************************************************************************
void do_out_data::mti_debug_cb (void* var, char* mti_value, char format_str)
{
    do_out_data* typed_var = reinterpret_cast<do_out_data*>(var);
    typed_var->get_string_value(format_str, mti_value);

    return;
}
