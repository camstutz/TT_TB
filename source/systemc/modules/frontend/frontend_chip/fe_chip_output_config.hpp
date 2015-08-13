/*!
 * @file fe_chip_output_config.hpp
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

#include "../../../data_formats/stub/stub_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class fe_chip_output_config
{
public:
    stub_config input_stub;
    stub_config output_stub;

    unsigned int bx_bits;
    unsigned int strip_bits;
    unsigned int pixel_bits;
    unsigned int bend_bits;
};
