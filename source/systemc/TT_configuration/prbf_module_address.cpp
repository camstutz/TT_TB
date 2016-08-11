/*!
 * @file prbf_module_address.cpp
 * @author Christian Amstutz
 * @date October 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "prbf_module_address.hpp"

// *****************************************************************************
prbf_module_address::prbf_module_address() :
        trigger_tower(0),
        rel_prb(0),
        rel_dtc(0),
        rel_module(0)
{}

// *****************************************************************************
prbf_module_address::prbf_module_address(const trigger_tower_t trigger_tower,
        const rel_prb_t rel_prb, const rel_dtc_t rel_dtc,
        const rel_module_t rel_module) :
        trigger_tower(trigger_tower),
        rel_prb(rel_prb),
        rel_dtc(rel_dtc),
        rel_module(rel_module)
{}

// *****************************************************************************
bool prbf_module_address::operator== (const prbf_module_address& rhs) const
{
    bool equal = true;

    equal &= (trigger_tower == rhs.trigger_tower);
    equal &= (rel_prb == rhs.rel_prb);
    equal &= (rel_dtc == rhs.rel_dtc);
    equal &= (rel_module == rhs.rel_module);

    return equal;
}

// *****************************************************************************
bool prbf_module_address::operator< (const prbf_module_address& rhs) const
{
    if (trigger_tower < rhs.trigger_tower)
    {
        return true;
    }

    if (trigger_tower == rhs.trigger_tower)
    {
        if (rel_prb < rhs.rel_prb)
        {
            return true;
        }

        if (rel_prb == rhs.rel_prb)
        {
            if (rel_dtc < rhs.rel_dtc)
            {
                return true;
            }

            if (rel_dtc == rhs.rel_dtc)
            {
                if(rel_module < rhs.rel_module)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, prbf_module_address const &v)
{
    os << "tow=" << v.trigger_tower;
    os << ",prb=" << v.rel_prb;
    os << ",dtc=" << v.rel_dtc;
    os << ",mod=" << v.rel_module;

    return os;
};
