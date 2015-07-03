/*!
 * @file configuration.hpp
 * @author Christian Amstutz
 * @date July 3, 2015
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

    // DTC
    configuration.dtc.input_nr = 3;
    configuration.dtc.collection_cycles = 8;

    configuration.dtc.controller.fe_collect_cycles = 8;

    configuration.dtc.input_unit.fe_id = 0xFF;
    configuration.dtc.input_unit.fe_collect_cycles = 8;

    configuration.dtc.output_unit.dtc_input_nr = 3;
    configuration.dtc.output_unit.fe_collect_cycles = 8;

    // Trigger Tower
    configuration.trigger_tower.layer_nr = 6;
    configuration.trigger_tower.dtc_per_prb = 1;
    configuration.trigger_tower.prb_nr = 2;
    configuration.trigger_tower.AM_boards_per_prb = 2;

    configuration.trigger_tower.data_organizer.dtc_input_nr =  2;
    configuration.trigger_tower.data_organizer.proc_unit_nr = 2;
    configuration.trigger_tower.data_organizer.input_collector.input_nr = 2;
    configuration.trigger_tower.data_organizer.demultiplexer.layer_nr = 1;
    configuration.trigger_tower.data_organizer.demultiplexer.proc_unit_nr = 2;
    configuration.trigger_tower.data_organizer.demultiplexer.timer_start = -25;
    configuration.trigger_tower.data_organizer.demultiplexer.bx_divider = 2;
    configuration.trigger_tower.data_organizer.demultiplexer.bx_offset = 0;

    configuration.trigger_tower.processor_organizer.do_input_nr = 2;
    configuration.trigger_tower.processor_organizer.processor_output_nr = 2;
    configuration.trigger_tower.processor_organizer.layer_nr = 6;
    configuration.trigger_tower.processor_organizer.input_collector.input_nr = 2;
    configuration.trigger_tower.processor_organizer.layer_splitter.layer_nr = 6;
    configuration.trigger_tower.processor_organizer.demultiplexer.layer_nr = 6;
    configuration.trigger_tower.processor_organizer.demultiplexer.proc_unit_nr = 2;
    configuration.trigger_tower.processor_organizer.demultiplexer.timer_start = -27;
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_divider = 4;
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_offset = 0;

    // AM Board
    configuration.am_board.layer_nr = 6;

    configuration.am_board.input_module.layer_nr = 6;
    configuration.am_board.input_module.controller.layer_nr = 6;

    return configuration;
}
