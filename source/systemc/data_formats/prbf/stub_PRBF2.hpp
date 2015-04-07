/*!
 * @file stub_PRBF2.hpp
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

#include "stub_PRBF1.hpp"

#include <string>
#include <sstream>

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************
class stub_PRBF2 : public stub_PRBF1
{
public:
    typedef unsigned int prb_t;

    stub_PRBF2();
    stub_PRBF2(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);              // no implementation, removes function from inherited class
    //stub_PRBF2(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);     // no implementation, removes function from inherited class
    stub_PRBF2(prb_t prb, dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);
    stub_PRBF2(prb_t prb, dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);

    void set(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);                // no implementation, removes function from inherited class
    //void set(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);       // no implementation, removes function from inherited class
    void set(prb_t prb, dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);
    void set(prb_t prb, dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);
    void set_prb(prb_t prb);
    prb_t get_prb() const;

    virtual std::string get_string() const;

protected:
    prb_t prb;
};

// *****************************************************************************
} // namespace PRBF
