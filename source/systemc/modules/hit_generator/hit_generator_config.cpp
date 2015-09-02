/*!
 * @file hit_generator_config.cpp
 * @author Christian Amstutz
 * @date August 31, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_generator_config.hpp"

// *****************************************************************************
hit_generator_config::hit_generator_config()
{
    set_LHC_clock_period_ns(LHC_CLOCK_PERIOD_NS_DEFAULT);
    input_file = INPUT_FILE_DEFAULT;

    return;
}

// *****************************************************************************
void hit_generator_config::set_LHC_clock_period_ns(
        unsigned int LHC_clock_period_ns)
{
    this->LHC_clock_period_ns = LHC_clock_period_ns;

    return;
}

// *****************************************************************************
void hit_generator_config::add_chips(sensor_module_config module)
{
    std::vector<chip_address> chips = module.address.get_chips(module.type);
    chip_addresses.insert(chip_addresses.end(), chips.begin(), chips.end());

    return;
}
