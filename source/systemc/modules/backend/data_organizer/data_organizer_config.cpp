/*!
 * @file data_organizer_config.cpp
 * @author Christian Amstutz
 * @date September 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "data_organizer_config.hpp"

// *****************************************************************************
void data_organizer_config::add_dtc(unsigned int dtc_id)
{
    DTCs.push_back(dtc_id);
    type.input_collector.input_nr = DTCs.size();

    return;
}

// *****************************************************************************
std::vector<unsigned int> data_organizer_config::get_dtcs() const
{
    return DTCs;
}
