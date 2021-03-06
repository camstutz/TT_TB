/*!
 * @file CIC_frame.cpp
 * @author Christian Amstutz
 * @date July 30, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "../CIC_frame/CIC_frame.hpp"

// *****************************************************************************
CIC_frame::CIC_frame()
{
    init();

    return;
}

// *****************************************************************************
CIC_frame::CIC_frame(stub_config stub_configuration) :
        stub_configuration(stub_configuration)
{
    init();

    return;
}

// *****************************************************************************
void CIC_frame::init()
{
    header_element = header_t();
    stub_vector.clear();
    reset_stub_ptr();
    trailer_element = trailer_t();

    return;
}

// *****************************************************************************
void CIC_frame::set_header(header_t new_header)
{
    header_element = new_header;

    return;
}

// *****************************************************************************
CIC_frame::header_t CIC_frame::get_header() const
{
    return header_element;
}

// *****************************************************************************
CIC_frame::trailer_t CIC_frame::get_trailer() const
{
    return trailer_element;
}

// *****************************************************************************
bool CIC_frame::is_CBC_frame() const
{
    if ((stub_count() == 0) | (header_element.get_fe_type() == header::CBC))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// *****************************************************************************
bool CIC_frame::is_MPA_frame() const
{
    if ((stub_count() == 0) | (header_element.get_fe_type() == header::MPA))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// *****************************************************************************
bool CIC_frame::add_stub(stub stub)
{
    bool success = false;

    if (stub.configuration == stub_configuration)
    {
        stub_vector.push_back(stub);
        if (stub.configuration.pixel_bits == 0)
        {
            header_element.set_fe_type(header::CBC);
        }
        else
        {
            header_element.set_fe_type(header::MPA);
        }
        header_element.set_stub_count(stub_count());

        success = true;
    }
    else
    {
        std::cerr << "CIC_frame: Wrong stub type." << std::endl;

        success = false;
    }

    return success;
}

// *****************************************************************************
CIC_frame::stub_vector_t::size_type
        CIC_frame::stub_count() const
{
    return stub_vector.size();
}

// *****************************************************************************
void CIC_frame::reset_stub_ptr()
{
    stub_it = stub_vector.begin();

    return;
}

// *****************************************************************************
bool CIC_frame::get_stub(stub& stub)
{
    bool valid = false;

    if (stub_it != stub_vector.end())
    {
        stub = *stub_it;
        ++stub_it;

        valid = true;
    }

    return valid;
}

// *****************************************************************************
bool CIC_frame::operator== (const CIC_frame& rhs) const
{
    bool equal = true;

    equal &= (rhs.header_element == header_element);
    equal &= (rhs.trailer_element == trailer_element);

    // tests for equal length, as the length is part of header
    if (equal)
    {
        equal &= std::equal(stub_vector.begin(), stub_vector.end(), rhs.stub_vector.begin());
    }

    return (equal);
}

// *****************************************************************************
CIC_frame& CIC_frame::operator= (const
        CIC_frame& rhs)
{
    header_element = rhs.header_element;
    trailer_element = rhs.trailer_element;

    stub_vector = rhs.stub_vector;

    reset_stub_ptr();

    return (*this);
}

// *****************************************************************************
std::string CIC_frame::get_string() const
{
    std::stringstream out_string;

    out_string << header_element << std::endl;
    typename stub_vector_t::const_iterator local_stub_it = stub_vector.begin();
    for(; local_stub_it != stub_vector.end(); ++local_stub_it)
    {
        stub stub = *local_stub_it;
        out_string << stub << std::endl;
    }
    out_string << trailer_element;

    return (out_string.str());
}

// *****************************************************************************
std::ostream& operator<< (std::ostream& stream, const CIC_frame&
        frame)
{
    stream << frame.get_string();

    return (stream);
}

// *****************************************************************************
void sc_trace(sc_trace_file* tf, const CIC_frame& v,
        const std::string& name)
{
    std::cerr << "CIC_frame: sc_trace() not implemented." << std::endl;

    return;
}
