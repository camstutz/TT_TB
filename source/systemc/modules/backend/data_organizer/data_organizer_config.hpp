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

public:
    typedef std::vector<unsigned int> DTC_table_t;

    data_organizer_type_config type;

    void add_dtc(unsigned int dtc_id);
    DTC_table_t get_dtcs() const;

private:
    DTC_table_t DTCs;
};
