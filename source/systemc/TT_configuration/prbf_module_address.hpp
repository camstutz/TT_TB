/*!
 * @file prbf_module_address.hpp
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
class prbf_module_address
{
public:
    unsigned int trigger_tower;
    unsigned int rel_prb;
    unsigned int rel_dtc;
    unsigned int rel_module;

    prbf_module_address();
    prbf_module_address(unsigned int trigger_tower, unsigned int rel_prb, unsigned int rel_dtc, unsigned int rel_module);

    bool operator== (const prbf_module_address& rhs) const;
    bool operator< (const prbf_module_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, prbf_module_address const &v);
};
