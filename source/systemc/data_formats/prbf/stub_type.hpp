/*!
 * @file stub_type.hpp
 * @author Christian Amstutz
 * @date April 2, 2015
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
namespace PRBF
{

class stub_type
{
public:
    virtual ~stub_type();

    virtual std::string get_string() const =0;

    friend std::ostream& operator<< (std::ostream& stream, const stub_type& stub);

private:
};

} // namespace PRBF
