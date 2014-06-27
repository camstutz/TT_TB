/*!
 * @file fe_cbc_out_data.cpp
 * @author Christian Amstutz
 * @date June 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fe_cbc_out_data.hpp"

// *****************************************************************************
fe_cbc_out_data::fe_cbc_out_data()
{
    dv = false;
    data = fe_cbc_stub_t(0,0);

    return;
}

// *****************************************************************************
void fe_cbc_out_data::set_dv(const data_valid_t dv_bit)
{
    dv = dv_bit;

    return;
}

// *****************************************************************************
fe_cbc_out_data::data_valid_t fe_cbc_out_data::get_dv() const
{
    return (dv);
}

// *****************************************************************************
void fe_cbc_out_data::set_data(const fe_cbc_stub_t new_stub)
{
    this->data = new_stub;

    return;
}

// *****************************************************************************
fe_cbc_out_data::fe_cbc_stub_t fe_cbc_out_data::get_data() const
{
    return (data);
}

// *****************************************************************************
bool fe_cbc_out_data::operator == (const fe_cbc_out_data &rhs) const
{
  return (rhs.dv == dv && rhs.data == data );
}

// *****************************************************************************
fe_cbc_out_data& fe_cbc_out_data::operator = (const fe_cbc_out_data& rhs)
{
    dv = rhs.dv;
    data = rhs.data;

    return (*this);
}

// *****************************************************************************
size_t fe_cbc_out_data::get_max_value_length()
{
    // todo: think about the return value of length
    return (35);
}

// *****************************************************************************
void fe_cbc_out_data::get_string_value(char format_str, char* string_value)
{
    std::stringstream my_string;
    my_string << dv << "-" << data;
    std::strcpy (string_value, my_string.str().c_str());
    
    return;    
}

// *****************************************************************************
ostream& operator << (ostream &os, fe_cbc_out_data const &v)
{
    os << "[" << v.dv << v.data << "]";

    return (os);
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const fe_cbc_out_data &v,
        const std::string &name)
{
    sc_trace(tf, v.dv, name + ".dv");
    sc_trace(tf, v.data, name + ".data");

    return;
}

// *****************************************************************************
void fe_cbc_out_data::mti_debug_cb (void* var, char* mti_value, char format_str)
{
    fe_cbc_out_data* typed_var = reinterpret_cast<fe_cbc_out_data*>(var);
    typed_var->get_string_value(format_str, mti_value);

    return;
}
