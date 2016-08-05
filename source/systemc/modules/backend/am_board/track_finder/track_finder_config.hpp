/*!
 * @file track_finder_config.hpp
 * @author Christian Amstutz
 * @date September 9, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "hit_processor/hit_processor_config.hpp"
#include "road_processor/road_processor_config.hpp"
#include "am_chip/am_chip_config.hpp"
#include "pattern_memory/pattern_memory_config.hpp"
#include "hit_buffer/hit_buffer_config.hpp"

#include <string>

// *****************************************************************************
/*!
 * @brief
 */
class track_finder_config
{
friend class track_finder;

private:
    unsigned int layer_nr;

public:
    hit_processor_config hit_processor;
    road_processor_config road_processor;
    am_chip_config am_chip;
    pattern_memory_config pattern_memory;
    hit_buffer_config hit_buffer;

    std::string pattern_bank_file;

    track_finder_config();

    void set_layer_nr(unsigned int layer_nr);
};
