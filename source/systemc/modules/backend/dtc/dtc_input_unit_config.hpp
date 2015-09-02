/*!
 * @file dtc_input_unit_config.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/stub/stub_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class dtc_input_unit_config
{
public:
    stub_config CBC_input_stub;
    stub_config MPA_input_stub;

    unsigned int fe_collect_cycles;
    unsigned int fe_id;
};
