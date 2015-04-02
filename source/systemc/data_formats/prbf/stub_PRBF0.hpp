/*!
 * @file stub_PRBF0.hpp
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

#include "stub_PRBF.hpp"

#include <string>
#include <sstream>

// *****************************************************************************
class stub_PRBF0 : public stub_PRBF
{
public:
    virtual std::string get_string() const;

private:
};
