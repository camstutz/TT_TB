/*!
 * @file stub_type.hpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <string>

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
class stub_type
{
public:
    virtual ~stub_type();

    virtual std::string get_string() const =0;
};

std::ostream& operator<< (std::ostream& stream, const stub_type& stub);

// *****************************************************************************
} // namespace CIC
