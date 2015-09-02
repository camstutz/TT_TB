/*!
 * @file dtc_type_config.cpp
 * @author Christian Amstutz
 * @date September 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_type_config.hpp"

// *****************************************************************************
dtc_type_config::dtc_type_config()
{
    set_fe_collection_cycles(FE_COLLECTION_CYCLES_DEFAULT);

    return;
}

// *****************************************************************************
void dtc_type_config::set_fe_collection_cycles(unsigned int fe_collection_cycles)
{
    this->fe_collection_cycles = fe_collection_cycles;

    controller.fe_collect_cycles = fe_collection_cycles;
    input_unit.fe_collect_cycles = fe_collection_cycles;
    output_unit.fe_collect_cycles = fe_collection_cycles;

    return;
}
