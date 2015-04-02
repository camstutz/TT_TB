/*!
 * @file stub_PRBF0.cpp
 * @author Christian Amstutz
 * @date April 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_PRBF0.hpp"

// *****************************************************************************
std::string stub_PRBF0::get_string() const
{
    std::stringstream out_string;

    out_string << "[" << get_PRBF_string() << "]";

    return (out_string.str());
}
