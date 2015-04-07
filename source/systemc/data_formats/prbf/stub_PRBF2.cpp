/*!
 * @file stub_PRBF2.cpp
 * @author Christian Amstutz
 * @date April 7, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_PRBF2.hpp"

// *****************************************************************************
namespace PRBF {

// *****************************************************************************
stub_PRBF2::stub_PRBF2() : stub_PRBF1()
{
    set_prb(0);

    return;
}

// *****************************************************************************
stub_PRBF2::stub_PRBF2(prb_t prb, dtc_t dtc, fe_module_t fe_module,
        concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID,
        strip_t strip, bend_t bend) :
        stub_PRBF1(dtc, fe_module, concentrator_ID, fe_chip_ID, strip, bend)
{
    set_prb(prb);

    return;
}

// *****************************************************************************
stub_PRBF2::stub_PRBF2(prb_t prb, dtc_t dtc, fe_module_t fe_module,
        concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t
        strip, bend_t bend, z_t z) :
        stub_PRBF1(dtc, fe_module, concentrator_ID, fe_chip_ID, strip, bend, z)
{
    set_prb(prb);

    return;
}

// *****************************************************************************
void stub_PRBF2::set(prb_t prb, dtc_t dtc, fe_module_t fe_module,
        concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID,
        strip_t strip, bend_t bend)
{
    set_prb(prb);
    stub_PRBF1::set(dtc, fe_module, concentrator_ID, fe_chip_ID, strip, bend);

    return;
}

// *****************************************************************************
void stub_PRBF2::set(prb_t prb, dtc_t dtc, fe_module_t fe_module,
        concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t
        strip, bend_t bend, z_t z)
{
    set_prb(prb);
    stub_PRBF1::set(dtc, fe_module, concentrator_ID, fe_chip_ID, strip, bend, z);

    return;
}

// *****************************************************************************
void stub_PRBF2::set_prb(prb_t prb)
{
    this->prb = prb;

    return;
}

// *****************************************************************************
stub_PRBF2::prb_t stub_PRBF2::get_prb() const
{
    return (prb);
}

// *****************************************************************************
std::string stub_PRBF2::get_string() const
{
    std::stringstream out_string;

    out_string << "[";
    out_string << "prb=0x" << std::setw(1) << prb << ",";
    out_string << "dtc=0x" << std::setw(1) << dtc << ",";
    out_string << get_PRBF_string();
    out_string << "]";

    return (out_string.str());
}

// *****************************************************************************
}  // namespace PRBF
