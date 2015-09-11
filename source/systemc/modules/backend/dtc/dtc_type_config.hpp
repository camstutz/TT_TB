/*!
 * @file dtc_type_config.hpp
 * @author Christian Amstutz
 * @date September 11, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_controller_config.hpp"
#include "dtc_input_unit_config.hpp"
#include "dtc_output_unit_config.hpp"

#include "../../../TT_configuration/configuration_defaults.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class dtc_type_config
{
    friend class dtc;

private:
    unsigned int fe_collection_cycles;

public:
    unsigned int bx_buffer_FIFO_size;

    dtc_controller_config controller;
    dtc_input_unit_type_config input_unit;
    dtc_output_unit_config output_unit;

    dtc_type_config();

    void set_fe_collection_cycles(unsigned int fe_collection_cycles);
};
