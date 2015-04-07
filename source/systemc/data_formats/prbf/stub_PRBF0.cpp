/*!
 * @file stub_PRBF0.cpp
 * @author Christian Amstutz
 * @date April 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "stub_PRBF0.hpp"

// *****************************************************************************
namespace PRBF {

// *****************************************************************************
void stub_PRBF0::set(fe_module_t fe_module, concentrator_ID_t concentrator_ID,
        fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend)
{
    stub_PRBF::set(fe_module, concentrator_ID, fe_chip_ID, strip, bend);

    return;
}

// *****************************************************************************
void stub_PRBF0::set(fe_module_t fe_module, concentrator_ID_t concentrator_ID,
        fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z)
{
    stub_PRBF::set(fe_module, concentrator_ID, fe_chip_ID, strip, bend, z);

    return;
}

// *****************************************************************************
std::string stub_PRBF0::get_string() const
{
    std::stringstream out_string;

    out_string << "[" << get_PRBF_string() << "]";

    return (out_string.str());
}

// *****************************************************************************
} // namespace PRBF
