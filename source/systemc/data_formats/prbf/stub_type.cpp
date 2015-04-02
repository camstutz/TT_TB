/*!
 * @file stub_type.cpp
 * @author Christian Amstutz
 * @date April 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_type.hpp"

using namespace PRBF;

// *****************************************************************************
stub_type::~stub_type()
{}

// *****************************************************************************
namespace PRBF
{

std::ostream& operator<< (std::ostream& stream, const stub_type& stub)
{
    stream << stub.get_string();

    return (stream);
}

}  // namespace PRBF

