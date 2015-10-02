/*!
 * @file baseline_configuration.hpp
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

#include "track_trigger_config.hpp"

inline track_trigger_config baseline_config()
{
    track_trigger_config configuration;

    // CBC front-end

    configuration.cbc_sensor_module.fe_chip_per_side = 8;
    configuration.cbc_sensor_module.side_count = 2;

    configuration.cbc_sensor_module.frontend_chip.max_stubs_per_cycle = 3;
    configuration.cbc_sensor_module.frontend_chip.collection_cycles = 1;
    configuration.cbc_sensor_module.frontend_chip.latency_cycles = 0;

    configuration.cbc_sensor_module.frontend_chip.input_stub.valid_bits = 0;
    configuration.cbc_sensor_module.frontend_chip.input_stub.bx_bits = 0;
    configuration.cbc_sensor_module.frontend_chip.input_stub.fechip_bits = 0;
    configuration.cbc_sensor_module.frontend_chip.input_stub.strip_bits = 8;
    configuration.cbc_sensor_module.frontend_chip.input_stub.bend_bits = 5;
    configuration.cbc_sensor_module.frontend_chip.input_stub.pixel_bits = 0;
    configuration.cbc_sensor_module.frontend_chip.output_stub = configuration.cbc_sensor_module.frontend_chip.input_stub;

    configuration.cbc_sensor_module.data_concentrator.output_stub = configuration.mpa_sensor_module.frontend_chip.output_stub;
    configuration.cbc_sensor_module.data_concentrator.output_stub.valid_bits = 1;
    configuration.cbc_sensor_module.data_concentrator.output_stub.bx_bits = 3;
    configuration.cbc_sensor_module.data_concentrator.fe_chips_count = 8;
    configuration.cbc_sensor_module.data_concentrator.max_output_stubs = 12;
    configuration.cbc_sensor_module.data_concentrator.output_window_cycles = 8;
    configuration.cbc_sensor_module.data_concentrator.delay_cycles = 0;
    configuration.cbc_sensor_module.data_concentrator.frontend_chip_type = configuration.cbc_sensor_module.frontend_chip;

    configuration.cbc_sensor_module.gbt.input_link_count = 2;

    // MPA front-end

    configuration.mpa_sensor_module.frontend_chip.max_stubs_per_cycle = 2;
    configuration.mpa_sensor_module.frontend_chip.collection_cycles = 2;
    configuration.mpa_sensor_module.frontend_chip.latency_cycles = 0;

    configuration.mpa_sensor_module.frontend_chip.input_stub.valid_bits = 0;
    configuration.mpa_sensor_module.frontend_chip.input_stub.bx_bits = 1;
    configuration.mpa_sensor_module.frontend_chip.input_stub.fechip_bits = 0;
    configuration.mpa_sensor_module.frontend_chip.input_stub.strip_bits = 8;
    configuration.mpa_sensor_module.frontend_chip.input_stub.bend_bits = 5;
    configuration.mpa_sensor_module.frontend_chip.input_stub.pixel_bits = 4;

    configuration.mpa_sensor_module.frontend_chip.output_stub = configuration.mpa_sensor_module.frontend_chip.input_stub;
    configuration.mpa_sensor_module.frontend_chip.output_stub.bx_bits = 1;

    configuration.mpa_sensor_module.data_concentrator.output_stub = configuration.mpa_sensor_module.frontend_chip.output_stub;
    configuration.mpa_sensor_module.data_concentrator.output_stub.valid_bits = 1;
    configuration.mpa_sensor_module.data_concentrator.output_stub.bx_bits = 3;
    configuration.mpa_sensor_module.data_concentrator.fe_chips_count = 8;
    configuration.mpa_sensor_module.data_concentrator.max_output_stubs = 10;
    configuration.mpa_sensor_module.data_concentrator.output_window_cycles = 8;
    configuration.mpa_sensor_module.data_concentrator.delay_cycles = 0;
    configuration.mpa_sensor_module.data_concentrator.frontend_chip_type = configuration.mpa_sensor_module.frontend_chip;

    configuration.mpa_sensor_module.fe_chip_per_side = 8;
    configuration.mpa_sensor_module.side_count = 2;

    configuration.mpa_sensor_module.gbt.input_link_count = 2;

    // Hit Generator
    configuration.hit_generator.output_stub_cbc = configuration.mpa_sensor_module.frontend_chip.input_stub;
    configuration.hit_generator.output_stub_mpa = configuration.mpa_sensor_module.frontend_chip.input_stub;

    // DTC
    configuration.dtc.set_fe_collection_cycles(8);
    configuration.dtc.bx_buffer_FIFO_size = 20;
    configuration.dtc.input_unit.CBC_input_stub = configuration.cbc_sensor_module.frontend_chip.input_stub;
    configuration.dtc.input_unit.MPA_input_stub = configuration.mpa_sensor_module.frontend_chip.input_stub;

    // Trigger Tower
    configuration.trigger_tower.set_dtc_per_prb(2);
    configuration.trigger_tower.set_prb_nr(4);
    configuration.trigger_tower.set_AM_boards_per_prb(2);

    configuration.trigger_tower.data_organizer.input_collector.input_nr = 1;
    configuration.trigger_tower.data_organizer.demultiplexer.bx_divider = 1;
    configuration.trigger_tower.data_organizer.demultiplexer.bx_offset = 0;
    configuration.trigger_tower.data_organizer.demultiplexer.timer_start = -25;

    configuration.trigger_tower.processor_organizer.set_do_input_nr(4);
    configuration.trigger_tower.processor_organizer.input_collector.input_nr = 2;
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_divider = 4;
    configuration.trigger_tower.processor_organizer.demultiplexer.timer_start = -40;

    // AM Board
    configuration.trigger_tower.am_board.track_finder.hit_processor.hit_processor_one_layer.SS_width_bits = 2;
    configuration.trigger_tower.am_board.track_finder.am_chip.set_road_detection_threshold(5);
    configuration.trigger_tower.am_board.track_finder.hit_buffer.set_SS_width_bit(2);
    configuration.trigger_tower.am_board.track_finder.pattern_bank_file = "data/pattern_banks/text_binary_test_patterns.txt";

    // Road Analyzer
    configuration.road_analyzer.output_file = "data/output/roads.txt";
    configuration.road_analyzer.nr_inputs = 8;
    configuration.road_analyzer.nr_layers = 6;

    configuration.read_track_trigger_config("source/systemc/TT_configuration/baseline", "data/configuration/baseline_Eta6_Phi8.csv");

    return configuration;
}
