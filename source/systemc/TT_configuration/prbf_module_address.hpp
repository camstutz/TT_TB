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
    typedef unsigned int trigger_tower_t ;
    typedef unsigned int rel_prb_t;
    typedef unsigned int rel_dtc_t;
    typedef unsigned int rel_module_t;

    trigger_tower_t trigger_tower;
    rel_prb_t rel_prb;
    rel_dtc_t rel_dtc;
    rel_module_t rel_module;

    prbf_module_address();
    prbf_module_address(const trigger_tower_t trigger_tower, const rel_prb_t rel_prb, const rel_dtc_t rel_dtc, const rel_module_t rel_module);

    bool operator== (const prbf_module_address& rhs) const;
    bool operator< (const prbf_module_address& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, prbf_module_address const &v);
};
