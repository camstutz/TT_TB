/*!
 * @file stub_PRBF1.cpp
 * @author Christian Amstutz
 * @date April 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_PRBF1.hpp"

// *****************************************************************************
stub_PRBF1::stub_PRBF1() : stub_PRBF()
{
    set_dtc(0);

    return;
}

// *****************************************************************************
stub_PRBF1::stub_PRBF1(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t
        concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend) :
                stub_PRBF(fe_module, concentrator_ID, fe_chip_ID, strip, bend)
{
    set_dtc(dtc);

    return;
}

// *****************************************************************************
stub_PRBF1::stub_PRBF1(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t
        concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend,
        z_t z) :
        stub_PRBF(fe_module, concentrator_ID, fe_chip_ID, strip, bend, z)
{
    set_dtc(dtc);

    return;
}

// *****************************************************************************
void stub_PRBF1::set(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend)
{
    set_dtc(dtc);
    stub_PRBF::set(fe_module, concentrator_ID, fe_chip_ID, strip, bend);

    return;
}

// *****************************************************************************
void stub_PRBF1::set(dtc_t dtc, fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z)
{
    set_dtc(dtc);
    stub_PRBF::set(fe_module, concentrator_ID, fe_chip_ID, strip, bend, z);

    return;
}

// *****************************************************************************
void stub_PRBF1::set_dtc(dtc_t dtc)
{
    this->dtc = dtc;

    return;
}

// *****************************************************************************
stub_PRBF1::dtc_t stub_PRBF1::get_dtc() const
{
    return (dtc);
}

// *****************************************************************************
std::string stub_PRBF1::get_string() const
{
    std::stringstream out_string;

    out_string << "[";
    out_string << "dtc=0x" << std::setw(1) << dtc << ",";
    out_string << get_PRBF_string();
    out_string << "]";

    return (out_string.str());
}
