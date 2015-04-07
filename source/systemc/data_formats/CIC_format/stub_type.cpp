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

using namespace CIC;

// *****************************************************************************
stub_type::~stub_type()
{}

// *****************************************************************************
namespace CIC
{

std::ostream& operator<< (std::ostream& stream, const stub_type& stub)
{
    stream << stub.get_string();

    return (stream);
}

}  // namespace CIC

