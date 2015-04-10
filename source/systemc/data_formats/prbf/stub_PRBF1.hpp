/*!
 * @file stub_PRBF1.hpp
 * @author Christian Amstutz
 * @date April 10, 2015
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
namespace PRBF
{

// *****************************************************************************
class stub_PRBF1 : public stub_PRBF
{
public:
    typedef unsigned int dtc_t;

    stub_PRBF1();
    stub_PRBF1(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);
    stub_PRBF1(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);

    void set(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);
    void set(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);
    void set_dtc(dtc_t dtc);
    dtc_t get_dtc() const;

    bool operator== (const stub_PRBF1& rhs) const;

    virtual std::string get_string() const;

protected:
    dtc_t dtc;
};

// *****************************************************************************
} // namespace PRBF
