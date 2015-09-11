/*!
 * @file dtc_input_unit_config.hpp
 * @author Christian Amstutz
 * @date September, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_input_unit_type_config.hpp"


// *****************************************************************************
/*!
 * @brief
 */
class dtc_input_unit_config
{
public:
    dtc_input_unit_type_config type;

    unsigned int fe_id;
};
