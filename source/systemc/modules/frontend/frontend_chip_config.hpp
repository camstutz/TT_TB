/*!
 * @file frontend_chip_config.hpp
 * @author Christian Amstutz
 * @date July 28, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "fe_chip_output_config.hpp"
#include "../../data_formats/stub/stub_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class frontend_chip_config
{
public:
    stub_config input_stub;
    stub_config output_stub;

    unsigned int max_stubs_per_cycle;
    unsigned int collection_cycles;
};
