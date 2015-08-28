/*!
 * @file data_organizer_config.hpp
 * @author Christian Amstutz
 * @date August 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "data_organizer_type_config.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class data_organizer_config
{
public:
    data_organizer_type_config* type;

    std::vector<unsigned int> DTCs;
};
