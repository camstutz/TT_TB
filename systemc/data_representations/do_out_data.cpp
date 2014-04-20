/*!
 * @file do_out_data.cpp
 * @author Christian Amstutz
 * @date Apr 20, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "do_out_data.hpp"

// *****************************************************************************
do_out_data::do_out_data()
{
	set_data_stub(do_stub_t());

    return;
}

// *****************************************************************************
do_out_data::do_out_data(const do_stub_t stub_data)
{
	set_data_stub(stub_data);

    return;
}

// *****************************************************************************
do_out_data::do_out_data(const time_stamp_t time_stamp)
{
	set_data_time_stamp(time_stamp);

    return;
}

// *****************************************************************************
do_out_data::time_stamp_flag_t do_out_data::get_time_stamp_flag() const
{
	return (data[time_stamp_flag_pos].to_bool());
}

// *****************************************************************************
void do_out_data::set_data_stub(const do_stub_t new_stub)
{
	set_time_stamp_flag(false);
    data(time_stamp_flag_pos-1,0) = new_stub.get_bit_vector();

    return;
}

// *****************************************************************************
void do_out_data::set_data_time_stamp(const time_stamp_t new_time_stamp)
{
	set_time_stamp_flag(true);
	data(time_stamp_flag_pos-1,0) = new_time_stamp;

	return;
}

// *****************************************************************************
do_out_data::data_t do_out_data::get_data() const
{
    return (data);
}

// *****************************************************************************
do_out_data::do_stub_t do_out_data::get_data_stub() const
{
	return (do_stub_t((sc_bv<16>)data));
}

// *****************************************************************************
do_out_data::time_stamp_t do_out_data::get_data_time_stamp() const
{
	return data(time_stamp_flag_pos-1,0);
}

// *****************************************************************************
bool do_out_data::operator == (const do_out_data &rhs) const
{
    return (rhs.data == data);
}

// *****************************************************************************
do_out_data& do_out_data::operator = (const do_out_data& rhs)
{
    data = rhs.data;

    return (*this);
}

// *****************************************************************************
ostream& operator << (ostream &os, do_out_data const &v)
{
	if (v.get_time_stamp_flag() == false)
	{
		os << "[" << v.get_data_stub() << "]";
	}
	else
	{
		os << "ts=" << v.get_data_time_stamp().to_uint();
	}

	return (os);
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const do_out_data &v, const std::string &name)
{
	sc_trace(tf, v.data, name + ".data");

	return;
}

// *****************************************************************************
void do_out_data::set_time_stamp_flag(const time_stamp_flag_t time_stamp_flag)
{
	data[time_stamp_flag_pos] = time_stamp_flag;

	return;
}
