/*!
 * @file dtc_buffer_element.cpp
 * @author Christian Amstutz
 * @date July 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_buffer_element.hpp"

// *****************************************************************************
ostream& operator<< (ostream &os, dtc_buffer_element const &v)
{
    os << "BX:";
    os << v.first;
    os << ", Stub element:";
    os << v.second << std::endl;

    return os;
}

// *****************************************************************************
void sc_trace(sc_trace_file* tf, const dtc_buffer_element& v, const std::string& name)
{
    std::cerr << "No implementation of dtc_buffer_element.sc_trace()" << std::endl;

    return;
}
