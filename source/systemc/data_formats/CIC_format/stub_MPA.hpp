/*!
 * @file stub_MPA.hpp
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

#include "stub_type.hpp"
#include "stub_CBC.hpp"

#include <string>
#include <sstream>
#include <iomanip>

// *****************************************************************************
namespace CIC
{

// *****************************************************************************
class stub_MPA : public stub_CBC
{
public:
    typedef unsigned int z_t;

    stub_MPA();
    stub_MPA(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chipID, strip_t strip, bend_t bend, z_t z);
    virtual ~stub_MPA();

    void set_z(z_t bend);
    z_t get_z() const;

    virtual std::string get_string() const;

protected:
    z_t z;

    void set(bunch_crossing_t bunch_crossing, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);
};

// *****************************************************************************
} // namespace CIC
