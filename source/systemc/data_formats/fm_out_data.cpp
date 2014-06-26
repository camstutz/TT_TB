/*!
 * @file fm_out_data.cpp
 * @author Christian Amstutz
 * @date June 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fm_out_data.hpp"

// *****************************************************************************
fm_out_data::fm_out_data()
{
    initialize_stub(false, fm_stub_t());

    return;
}

// *****************************************************************************
fm_out_data::fm_out_data(const fm_stub_t stub_data)
{
    initialize_stub(true, stub_data);

    return;
}

// *****************************************************************************
fm_out_data::fm_out_data(const data_valid_flag_t data_valid,
        const fm_stub_t stub_data)
{
    initialize_stub(data_valid, stub_data);

    return;
}

// *****************************************************************************
fm_out_data::fm_out_data(const time_stamp_t time_stamp)
{
	set_data_time_stamp(time_stamp);

    return;
}

// *****************************************************************************
void fm_out_data::set_data_valid_flag(const data_valid_flag_t new_data_valid)
{
    data[data_valid_pos] = new_data_valid;

    return;
}

// *****************************************************************************
void fm_out_data::set_data_stub(const fm_stub_t new_stub)
{
	set_time_stamp_flag(false);
    data(time_stamp_flag_pos-1,0) = new_stub.get_bit_vector();

    return;
}

// *****************************************************************************
void fm_out_data::set_data_time_stamp(const time_stamp_t new_time_stamp)
{
    set_data_valid_flag(true);
    set_time_stamp_flag(true);
	data(time_stamp_flag_pos-1,0) = new_time_stamp;

	return;
}

// *****************************************************************************
fm_out_data::data_valid_flag_t fm_out_data::get_data_valid_flag() const
{
    return (data[data_valid_pos].to_bool());
}

// *****************************************************************************
fm_out_data::time_stamp_flag_t fm_out_data::get_time_stamp_flag() const
{
    return (data[time_stamp_flag_pos].to_bool());
}

// *****************************************************************************
fm_out_data::data_t fm_out_data::get_data() const
{
    return (data);
}

// *****************************************************************************
fm_out_data::fm_stub_t fm_out_data::get_data_stub() const
{
	return (fm_stub_t((payload_t)data));
}

// *****************************************************************************
fm_out_data::time_stamp_t fm_out_data::get_data_time_stamp() const
{
	return (data(time_stamp_flag_pos-1, 0));
}

// *****************************************************************************
bool fm_out_data::operator == (const fm_out_data &rhs) const
{
    return (rhs.data == data);
}

// *****************************************************************************
fm_out_data& fm_out_data::operator = (const fm_out_data& rhs)
{
    data = rhs.data;

    return (*this);
}

// *****************************************************************************
size_t fm_out_data::get_max_value_length()
{
    // todo: think about the return value of length
    return 20;
}

// *****************************************************************************
void fm_out_data::get_string_value(char format_str, char* string_value)
{
    std::stringstream my_string;
    my_string <<  data;
    std::strcpy (string_value, my_string.str().c_str());

    return;
}

// *****************************************************************************
ostream& operator << (ostream &os, fm_out_data const &v)
{
	if (v.get_time_stamp_flag() == false)
	{
		os << "[" << v.get_data_valid_flag() << v.get_data_stub() << "]";
	}
	else
	{
		os << "[" << v.get_data_valid_flag() << ","
		        << "ts=" << v.get_data_time_stamp().to_uint() << "]";
	}

	return (os);
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const fm_out_data &v, const std::string &name)
{
	sc_trace(tf, v.data, name + ".data");

	return;
}

// *****************************************************************************
void fm_out_data::mti_debug_cb (void* var, char* mti_value, char format_str)
{
    fm_out_data* typed_var = reinterpret_cast<fm_out_data*>(var);
    typed_var->get_string_value(format_str, mti_value);

    return;
}

// *****************************************************************************
void fm_out_data::initialize_stub(const data_valid_flag_t data_valid,
        const fm_stub_t stub_data)
{
    set_data_valid_flag(data_valid);
    set_data_stub(stub_data);

    return;
}

// *****************************************************************************
void fm_out_data::set_time_stamp_flag(const time_stamp_flag_t time_stamp_flag)
{
	data[time_stamp_flag_pos] = time_stamp_flag;

	return;
}