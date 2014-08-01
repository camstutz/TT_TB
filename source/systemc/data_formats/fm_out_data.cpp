/*!
 * @file fm_out_data.cpp
 * @author Christian Amstutz
 * @date Aug 1, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fm_out_data.hpp"

// *****************************************************************************
fm_out_data::fm_out_data(const fm_stub_t stub_data)
{
    set_data_stub(stub_data);

    return;
}

// *****************************************************************************
fm_out_data::fm_out_data(const timestamp_t timestamp)
{
	set_timestamp(timestamp);

    return;
}

// *****************************************************************************
fm_out_data::~fm_out_data()
{}

// *****************************************************************************
void fm_out_data::set_data_stub(const fm_stub_t new_stub)
{
    timestamp_flag = STUB;
    payload = new_stub.get_bitvector().to_uint();

    return;
}

// *****************************************************************************
fm_out_data::fm_stub_t fm_out_data::get_data_stub() const
{
    // TODO: check if data is stub

    fm_stub_t return_stub;
    return_stub.set_bitvector(fm_stub_bv_t(payload));

    return (return_stub);
}

// *****************************************************************************
void fm_out_data::set_timestamp(const timestamp_t new_timestamp)
{
    timestamp_flag = STUB;
	payload = new_timestamp;

	return;
}

// *****************************************************************************
fm_out_data::timestamp_t fm_out_data::get_timestamp() const
{
    // TODO: check if value us timestamp

    return (payload);
}

// *****************************************************************************
fm_out_data::timestamp_flag_t fm_out_data::is_timestamp() const
{
    return (timestamp_flag);
}

// *****************************************************************************
fm_out_data::full_bv_t fm_out_data::get_bitvector() const
{
    full_bv_t output_bv;

    output_bv(payload_start+payload_width-1, payload_start) = payload_bv_t(payload);
    output_bv(timestamp_flag_start+timestamp_flag_width-1, timestamp_flag_start) = timestamp_flag;

    return (output_bv);
}

// *****************************************************************************
void fm_out_data::set_bitvector(full_bv_t bit_vector)
{
    // TODO: use setter functions for range check

    payload = bit_vector(payload_start+payload_width-1, payload_start).to_uint();
    timestamp_flag = bit_vector(timestamp_flag_start+timestamp_flag_width-1, timestamp_flag_start).to_uint();

    return;
}

// *****************************************************************************
size_t fm_out_data::get_max_string_length() const
{
    // todo: relative to widths of fields

    return (27);
}

// *****************************************************************************
std::string fm_out_data::get_string() const
{
    std::stringstream out_string;
    out_string << "[" << "TF=" << is_timestamp();
    if (is_timestamp() == STUB)
    {
        out_string << get_data_stub();
    }
    else
    {
        out_string << "T=" << get_timestamp();
    }
    out_string << "]";

    return (out_string.str());
}

// *****************************************************************************
bool fm_out_data::operator== (const fm_out_data &rhs) const
{
    return (is_equal(rhs));
}

// *****************************************************************************
fm_out_data& fm_out_data::operator= (const fm_out_data & rhs)
{
    copy(rhs);

    return (*this);
}

// *****************************************************************************
bool fm_out_data::is_equal(const fm_out_data& rhs) const
{
    bool equal = false;
    equal = equal & (timestamp_flag == rhs.timestamp_flag);
    equal = equal & (payload == rhs.payload);

    return (equal);
}

// *****************************************************************************
void fm_out_data::copy(const fm_out_data& original)
{
    if (original.is_timestamp())
    {
        set_timestamp(original.get_timestamp());
    }
    else
    {
        set_data_stub(original.get_data_stub());
    }

    return;
}

// *****************************************************************************
void sc_trace(sc_trace_file *tf, const fm_out_data &v, const std::string &name)
{
    sc_trace(tf, v.timestamp_flag, name + ".ts_flag");
	sc_trace(tf, v.payload, name + ".data");

	return;
}
