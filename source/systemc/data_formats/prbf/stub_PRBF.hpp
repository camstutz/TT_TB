/*!
 * @file stub_PRBF.hpp
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

#include "stub_type.hpp"

#include <string>
#include <sstream>
#include <iomanip>

// *****************************************************************************
namespace PRBF
{

// *****************************************************************************
class stub_PRBF : public stub_type
{
public:
    typedef unsigned int fe_module_t;
    typedef unsigned int concentrator_ID_t;
    typedef unsigned int fe_chip_ID_t;
    typedef unsigned int strip_t;
    typedef unsigned int bend_t;
    typedef unsigned int z_t;

    stub_PRBF();
    stub_PRBF(fe_module_t, concentrator_ID_t, fe_chip_ID_t, strip_t, bend_t);
    stub_PRBF(fe_module_t, concentrator_ID_t, fe_chip_ID_t, strip_t, bend_t, z_t);
    virtual ~stub_PRBF();

    void set_fe_module(fe_module_t fe_module);
    fe_module_t get_fe_module() const;
    void set_concentrator_ID(concentrator_ID_t concentrator_ID);
    concentrator_ID_t get_concentrator_ID() const;
    void set_fe_chip_ID(fe_chip_ID_t fe_chip_ID);
    fe_chip_ID_t get_fe_chip_ID() const;
    void set_strip(strip_t strip);
    strip_t get_strip() const;
    void set_bend(bend_t bend);
    bend_t get_bend() const;
    void set_z(z_t z);
    z_t get_z() const;

    bool operator== (const stub_PRBF& rhs) const;

    virtual std::string get_string() const =0;

protected:
    fe_module_t fe_module;
    concentrator_ID_t concentrator_ID;
    fe_chip_ID_t fe_chip_ID;
    strip_t strip;
    bend_t bend;
    z_t z;

    void set(fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend);
    void set(fe_module_t fe_module, concentrator_ID_t concentrator_ID, fe_chip_ID_t fe_chip_ID, strip_t strip, bend_t bend, z_t z);

    std::string get_PRBF_string() const;
};

// *****************************************************************************
} // namespace PRBF
