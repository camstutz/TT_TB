/*!
 * @file data_organizer_config.hpp
 * @author Christian Amstutz
 * @date September 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "data_organizer_type_config.hpp"

#include <vector>

// *****************************************************************************
/*!
 * @brief
 */
class data_organizer_config
{
    friend class data_organizer;

private:
    std::vector<unsigned int> DTCs;

public:
    data_organizer_type_config type;

    void add_dtc(unsigned int dtc_id);
    std::vector<unsigned int> get_dtcs() const;
};
