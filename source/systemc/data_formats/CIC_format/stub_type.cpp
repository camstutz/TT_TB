/*!
 * @file stub_type.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_type.hpp"

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
stub_type::~stub_type()
{}

// *****************************************************************************
std::ostream& operator<< (std::ostream& stream, const stub_type& stub)
{
    stream << stub.get_string();

    return (stream);
}

// *****************************************************************************
}  // namespace CIC

