/*!
 * @file dtc_buffer_element.hpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/prbf/PRBF.hpp"

#include <utility>

class dtc_buffer_element : public std::pair<PRBF_0::header_t::bunch_crossing_ID_t, PRBF_0::stub_element_t>
{
    friend ostream& operator<< (ostream &os, dtc_buffer_element const &v);
    friend void sc_trace(sc_trace_file* tf, const dtc_buffer_element& v, const std::string& name);
};

