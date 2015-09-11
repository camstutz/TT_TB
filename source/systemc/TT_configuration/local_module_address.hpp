/*!
 * @file sensor_module_address.hpp
 * @author Christian Amstutz
 * @date September 10, 2015
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
    unsigned int trigger_tower;
    unsigned int rel_prb;
    unsigned int rel_dtc;
    unsigned int rel_module;

    local_module_address();
    local_module_address(unsigned int trigger_tower, unsigned int rel_prb, unsigned int rel_dtc, unsigned int rel_module);

    bool operator== (const local_module_address& rhs) const;
    bool operator< (const local_module_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, local_module_address const &v);
};
