/*!
 * @file sector_id.cpp
 * @author Christian Amstutz
 * @date September 24, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "sector_id.hpp"

// *****************************************************************************
sector_id::sector_id() :
        id(0),
        eta(0),
        phi(0)
{}

// *****************************************************************************
sector_id::sector_id(const unsigned int id, const unsigned int eta,
        const unsigned int phi) :
        id(id),
        eta(eta),
        phi(phi)
{}

// *****************************************************************************
bool sector_id::operator== (const sector_id& rhs) const
{
    bool equal = true;

    equal &= (id == rhs.id);
    equal &= (eta == rhs.eta);
    equal &= (phi == rhs.phi);

    return equal;
}

// *****************************************************************************
bool sector_id::operator< (const sector_id& rhs) const
{
    if (eta < rhs.eta)
    {
        return true;
    }

    if (eta == rhs.eta)
    {
        if (phi < rhs.phi)
        {
            return true;
        }
    }

    return false;
}

// *****************************************************************************
std::ostream& operator<< (std::ostream &os, sector_id const &v)
{
    os << "id=" << v.id;
    os << ",eta=" << v.eta;
    os << ",phi=" << v.phi;

    return os;
};
