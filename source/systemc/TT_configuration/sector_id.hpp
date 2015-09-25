/*!
 * @file sector_id.hpp
 * @author Christian Amstutz
 * @date September 24, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <ostream>

// *****************************************************************************
/*!
 * @brief
 */
class sector_id
{
public:
    unsigned int id;
    unsigned int eta;
    unsigned int phi;

    sector_id();
    sector_id(const unsigned int id, const unsigned int eta, const unsigned int phi);

    bool operator== (const sector_id& rhs) const;
    bool operator< (const sector_id& rhs) const;

    friend std::ostream& operator<< (std::ostream &os, sector_id const &v);
};
