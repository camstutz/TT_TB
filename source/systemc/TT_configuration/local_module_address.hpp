/*!
 * @file local_module_address.hpp
 * @author Christian Amstutz
 * @date October 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <ostream>

// *****************************************************************************
/*!
 * @brief
 */
class local_module_address
{
public:
    unsigned int layer;
    unsigned int ladder;
    unsigned int module;

    local_module_address();
    local_module_address(const unsigned int layer, const unsigned int ladder, const unsigned int module);

    bool operator== (const local_module_address& rhs) const;
    bool operator< (const local_module_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, local_module_address const &v);
};
