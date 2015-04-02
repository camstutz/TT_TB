/*!
 * @file stub_PRBF0.hpp
 * @author Christian Amstutz
 * @date April 2, 2015
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
class stub_PRBF0 : public stub_PRBF
{
public:
    void set(fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);
    void set(fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);

    virtual std::string get_string() const;

private:
};
