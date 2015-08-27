/*!
 * @file configuration.hpp
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

    configuration.cbc_frontend_chip.max_stubs_per_cycle = 3;
    configuration.cbc_frontend_chip.collection_cycles = 1;
    configuration.cbc_frontend_chip.latency_cycles = 0;

    configuration.cbc_frontend_chip.input_stub.valid_bits = 0;
    configuration.cbc_frontend_chip.input_stub.bx_bits = 0;
    configuration.cbc_frontend_chip.input_stub.fechip_bits = 0;
    configuration.cbc_frontend_chip.input_stub.strip_bits = 8;
    configuration.cbc_frontend_chip.input_stub.bend_bits = 5;
    configuration.cbc_frontend_chip.input_stub.pixel_bits = 0;
    configuration.cbc_frontend_chip.output_stub = configuration.cbc_frontend_chip.input_stub;

    configuration.cbc_data_concentrator.frontend_chip_type = configuration.cbc_frontend_chip;
    configuration.cbc_data_concentrator.output_stub = configuration.cbc_frontend_chip.output_stub;
    configuration.cbc_data_concentrator.output_stub.valid_bits = 1;
    configuration.cbc_data_concentrator.output_stub.bx_bits = 3;
    configuration.cbc_data_concentrator.fe_chips_count = 8;
    configuration.cbc_data_concentrator.max_output_stubs = 12;
    configuration.cbc_data_concentrator.output_window_cycles = 8;
    configuration.cbc_data_concentrator.delay_cycles = 0;

    configuration.mpa_frontend_chip.max_stubs_per_cycle = 2;
    configuration.mpa_frontend_chip.collection_cycles = 2;
    configuration.mpa_frontend_chip.latency_cycles = 0;

    configuration.mpa_frontend_chip.input_stub.valid_bits = 0;
    configuration.mpa_frontend_chip.input_stub.bx_bits = 1;
    configuration.mpa_frontend_chip.input_stub.fechip_bits = 0;
    configuration.mpa_frontend_chip.input_stub.strip_bits = 8;
    configuration.mpa_frontend_chip.input_stub.bend_bits = 5;
    configuration.mpa_frontend_chip.input_stub.pixel_bits = 4;

    configuration.mpa_frontend_chip.output_stub = configuration.mpa_frontend_chip.input_stub;
    configuration.mpa_frontend_chip.output_stub.bx_bits = 1;

    configuration.mpa_data_concentrator.frontend_chip_type = configuration.mpa_frontend_chip;
    configuration.mpa_data_concentrator.output_stub = configuration.mpa_frontend_chip.output_stub;
    configuration.mpa_data_concentrator.output_stub.valid_bits = 1;
    configuration.mpa_data_concentrator.output_stub.bx_bits = 3;
    configuration.mpa_data_concentrator.fe_chips_count = 8;
    configuration.mpa_data_concentrator.max_output_stubs = 10;
    configuration.mpa_data_concentrator.output_window_cycles = 8;
    configuration.mpa_data_concentrator.delay_cycles = 0;

    // Configure general GBT module
    configuration.gbt.input_link_count = 2;

    configuration.cbc_sensor_module.fe_chip_per_side = 8;
    configuration.cbc_sensor_module.side_count = 2;
    configuration.cbc_sensor_module.frontend_chip = configuration.cbc_frontend_chip;
    configuration.cbc_sensor_module.data_concentrator = configuration.cbc_data_concentrator;
    configuration.cbc_sensor_module.gbt = configuration.gbt;
    configuration.cbc_sensor_module_test.type = &configuration.cbc_sensor_module;

    configuration.mpa_sensor_module.fe_chip_per_side = 8;
    configuration.mpa_sensor_module.side_count = 2;
    configuration.mpa_sensor_module.frontend_chip = configuration.mpa_frontend_chip;
    configuration.mpa_sensor_module.data_concentrator = configuration.mpa_data_concentrator;
    configuration.mpa_sensor_module.gbt = configuration.gbt;
    configuration.mpa_sensor_module_test.type = &configuration.mpa_sensor_module;

    // Hit Generator
    configuration.hit_generator.output_stub_cbc = configuration.cbc_frontend_chip.input_stub;
    configuration.hit_generator.output_stub_mpa = configuration.mpa_frontend_chip.input_stub;

    configuration.sensor_modules.push_back(sensor_module_config(&configuration.mpa_sensor_module, 0, sensor_module_address(0,0,0)));
    configuration.sensor_modules.push_back(sensor_module_config(&configuration.mpa_sensor_module, 1, sensor_module_address(1,0,0)));
    configuration.sensor_modules.push_back(sensor_module_config(&configuration.mpa_sensor_module, 2, sensor_module_address(2,0,0)));
    configuration.sensor_modules.push_back(sensor_module_config(&configuration.cbc_sensor_module, 3, sensor_module_address(3,0,0)));
    configuration.sensor_modules.push_back(sensor_module_config(&configuration.cbc_sensor_module, 4, sensor_module_address(4,0,0)));
    configuration.sensor_modules.push_back(sensor_module_config(&configuration.cbc_sensor_module, 5, sensor_module_address(5,0,0)));

    std::vector<chip_address> new_chips;
    for(auto module : configuration.sensor_modules)
    {
        new_chips = module.address.get_chips(*module.type);
        configuration.hit_generator.chip_addresses.insert(configuration.hit_generator.chip_addresses.end(), new_chips.begin(), new_chips.end());
    }

    // DTC

    configuration.dtc.collection_cycles = 8;
    configuration.dtc.controller.fe_collect_cycles = 8;
    configuration.dtc.input_unit.fe_id = 0xFF;
    configuration.dtc.input_unit.fe_collect_cycles = 8;
    configuration.dtc.output_unit.fe_collect_cycles = 8;

    configuration.dtcs.resize(1);
    configuration.dtcs[0] = configuration.dtc;
    configuration.dtcs[0].sensor_modules.push_back(sensor_module_address(0,0,0));
    configuration.dtcs[0].sensor_modules.push_back(sensor_module_address(1,0,0));
    configuration.dtcs[0].sensor_modules.push_back(sensor_module_address(2,0,0));
    configuration.dtcs[0].sensor_modules.push_back(sensor_module_address(3,0,0));
    configuration.dtcs[0].sensor_modules.push_back(sensor_module_address(4,0,0));
    configuration.dtcs[0].sensor_modules.push_back(sensor_module_address(5,0,0));
    configuration.dtcs[0].output_unit.dtc_input_nr = configuration.dtcs[0].sensor_modules.size();

    // Trigger Tower
    configuration.trigger_tower.layer_nr = 6;
    configuration.trigger_tower.dtc_per_prb = 1;
    configuration.trigger_tower.prb_nr = 4;
    configuration.trigger_tower.AM_boards_per_prb = 2;

    configuration.trigger_tower.data_organizer.dtc_input_nr =  1;
    configuration.trigger_tower.data_organizer.proc_unit_nr = 4;
    configuration.trigger_tower.data_organizer.input_collector.input_nr = 1;
    configuration.trigger_tower.data_organizer.demultiplexer.bx_divider = 1;
    configuration.trigger_tower.data_organizer.demultiplexer.bx_offset = 0;
    configuration.trigger_tower.data_organizer.demultiplexer.layer_nr = 1;
    configuration.trigger_tower.data_organizer.demultiplexer.proc_unit_nr = 4;
    configuration.trigger_tower.data_organizer.demultiplexer.timer_start = -25;

    configuration.trigger_tower.processor_organizer.do_input_nr = 4;
    configuration.trigger_tower.processor_organizer.processor_output_nr = 2;
    configuration.trigger_tower.processor_organizer.layer_nr = 6;
    configuration.trigger_tower.processor_organizer.input_collector.input_nr = 2;
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_divider = 4;
    configuration.trigger_tower.processor_organizer.demultiplexer.layer_nr = 6;
    configuration.trigger_tower.processor_organizer.demultiplexer.proc_unit_nr = 2;
    configuration.trigger_tower.processor_organizer.demultiplexer.timer_start = -40;
    configuration.trigger_tower.processor_organizer.layer_splitter.layer_nr = 6;

    configuration.trigger_tower.processor_organizer.demultiplexer.bx_offset = 0;
    configuration.trigger_tower.processor_organizers.push_back(configuration.trigger_tower.processor_organizer);
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_offset = 1;
    configuration.trigger_tower.processor_organizers.push_back(configuration.trigger_tower.processor_organizer);
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_offset = 2;
    configuration.trigger_tower.processor_organizers.push_back(configuration.trigger_tower.processor_organizer);
    configuration.trigger_tower.processor_organizer.demultiplexer.bx_offset = 3;
    configuration.trigger_tower.processor_organizers.push_back(configuration.trigger_tower.processor_organizer);

    // AM Board
    configuration.trigger_tower.am_board.layer_nr = 6;

    configuration.trigger_tower.am_board.input_module.layer_nr = 6;
    configuration.trigger_tower.am_board.input_module.controller.layer_nr = 6;

    configuration.trigger_tower.am_board.track_finder.layer_nr = 6;

    configuration.trigger_tower.am_board.track_finder.hit_processor.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.am_chip.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.am_chip.road_detection_threshold = 5;
    configuration.trigger_tower.am_board.track_finder.am_chip.write_ctrl.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.road_processor.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.pattern_memory.layer_nr = 6;

    configuration.trigger_tower.am_board.track_finder.hit_buffer.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.hit_buffer.hit_buffer_write_ctrl.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.hit_buffer.hit_buffer_lookup_ctrl.layer_nr = 6;
    configuration.trigger_tower.am_board.track_finder.hit_buffer.hit_buffer_output_ctrl.layer_nr = 6;

    // Road Analyzer
    configuration.road_analyzer.output_file = "data/output/roads.txt";
    configuration.road_analyzer.nr_inputs = 8;
    configuration.road_analyzer.nr_layers = 6;

    return configuration;
}
