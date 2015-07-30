/*!
 * @file header.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "../CIC_frame/header.hpp"

// *****************************************************************************
namespace CIC
{

// *****************************************************************************

const header::hw_status_t header::status_OK  = 0x000;
const header::hw_status_t header::fe_0_ERROR = 0x001;
const header::hw_status_t header::fe_1_ERROR = 0x002;
const header::hw_status_t header::fe_2_ERROR = 0x004;
const header::hw_status_t header::fe_3_ERROR = 0x008;
const header::hw_status_t header::fe_4_ERROR = 0x010;
const header::hw_status_t header::fe_5_ERROR = 0x020;
const header::hw_status_t header::fe_6_ERROR = 0x040;
const header::hw_status_t header::fe_7_ERROR = 0x080;
const header::hw_status_t header::cic_ERROR  = 0x100;

// *****************************************************************************
header::header()
{
    set(header::CBC, 0, 0);
    set_stub_count(0);

    return;
}

// *****************************************************************************
header::header(fe_type_t fe_type, hw_status_t hw_status, bunch_crossing_t
        bunch_crossing)
{
    set(fe_type, hw_status, bunch_crossing);
    set_stub_count(0);

    return;
}

// *****************************************************************************
void header::set(fe_type_t fe_type, hw_status_t hw_status,
        bunch_crossing_t bunch_crossing)
{
    set_fe_type(fe_type);
    set_hw_status(hw_status);
    set_bunch_crossing(bunch_crossing);

    return;
}

// *****************************************************************************
void header::set_fe_type(fe_type_t fe_type)
{
    this->fe_type = fe_type;

    return;
}

// *****************************************************************************
header::fe_type_t header::get_fe_type() const
{
    return (fe_type);
}

// *****************************************************************************
void header::set_hw_status(hw_status_t hw_status)
{
    this->hw_status = hw_status;

    return;
}

// *****************************************************************************
header::hw_status_t header::get_hw_status() const
{
    return (hw_status);
}

// *****************************************************************************
void header::set_bunch_crossing(bunch_crossing_t bunch_crossing)
{
    this->bunch_crossing = bunch_crossing;

    return;
}

// *****************************************************************************
header::bunch_crossing_t header::get_bunch_crossing() const
{
    return (bunch_crossing);
}

// *****************************************************************************
header::stub_count_t header::get_stub_count() const
{
    return (stub_count);
}

// *****************************************************************************
bool header::operator== (const header& rhs) const
{
    bool equal = true;

    equal &= (rhs.fe_type == fe_type);
    equal &= (rhs.hw_status == hw_status);
    equal &= (rhs.bunch_crossing == bunch_crossing);
    equal &= (rhs.stub_count == stub_count);

    return (equal);
}

// *****************************************************************************
std::string header::get_string() const
{
    std::stringstream out_string;

    out_string << std::hex
                   << std::internal
                   << std::setfill('0');
    out_string << "[";
    if (fe_type == CBC)
    {
        out_string << "t=CBC,";
    }
    else
    {
        out_string << "t=MPA,";
    }
    std::bitset<9> hw_status_bin(hw_status);
    out_string << "st=" << hw_status_bin << ",";
    out_string << "bx=0x" << std::setw(3) << bunch_crossing << ",";
    out_string << "sc=0x" << std::setw(1) << stub_count;
    out_string << "]";

    return (out_string.str());
}

// *****************************************************************************
void header::set_stub_count(stub_count_t stub_count)
{
    this->stub_count = stub_count;

    return;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream& stream, const header& head)
{
    stream << head.get_string();

    return (stream);
}

// *****************************************************************************
} // namespace CIC
