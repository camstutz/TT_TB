/*!
 * @file configuration.hpp
 * @author Christian Amstutz
 * @date June 25, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "track_trigger_config.hpp"

track_trigger_config baseline_config()
{
    track_trigger_config configuration;

    configuration.cbc_frontend_chip.max_stubs_per_cycle = 3;
    configuration.cbc_frontend_chip.collection_cycles = 1;

    configuration.cbc_frontend_chip.output_format.bx_bits = 0;
    configuration.cbc_frontend_chip.output_format.strip_bits = 8;
    configuration.cbc_frontend_chip.output_format.pixel_bits = 0;
    configuration.cbc_frontend_chip.output_format.bend_bits = 5;

    configuration.cbc_data_concentrator.fe_chips_count = 8;
    configuration.cbc_data_concentrator.frontend_chip_type = configuration.cbc_frontend_chip;
    configuration.cbc_data_concentrator.max_output_stubs = 12;
    configuration.cbc_data_concentrator.output_window_cycles = 8;

    configuration.mpa_frontend_chip.max_stubs_per_cycle = 2;
    configuration.mpa_frontend_chip.collection_cycles = 2;

    configuration.mpa_frontend_chip.output_format.bx_bits = 1;
    configuration.mpa_frontend_chip.output_format.strip_bits = 8;
    configuration.mpa_frontend_chip.output_format.pixel_bits = 4;
    configuration.mpa_frontend_chip.output_format.bend_bits = 5;

    configuration.mpa_data_concentrator.fe_chips_count = 8;
    configuration.mpa_data_concentrator.frontend_chip_type = configuration.mpa_frontend_chip;
    configuration.mpa_data_concentrator.max_output_stubs = 10;
    configuration.mpa_data_concentrator.output_window_cycles = 8;

    configuration.trigger_tower.layer_nr = 6;
    configuration.trigger_tower.dtc_per_prb = 1;
    configuration.trigger_tower.prb_nr = 2;
    configuration.trigger_tower.dtc_per_prb = 2;

    //configuration.trigger_tower.processor_organizer.

    //configuration.trigger_tower.data_organizer

    return configuration;
}

