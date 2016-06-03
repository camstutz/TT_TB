/*!
 * @file track_trigger_config.hpp
 * @author Christian Amstutz
 * @date September 30, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../modules/hit_generator/hit_generator_config.hpp"
#include "../modules/frontend/frontend_chip/frontend_chip_config.hpp"
#include "../modules/frontend/data_concentrator/data_concentrator_config.hpp"
#include "../modules/frontend/sensor_module/sensor_module_config.hpp"
#include "../modules/frontend/gbt/gbt_config.hpp"
#include "../modules/backend/dtc/dtc_type_config.hpp"
#include "../modules/backend/dtc/dtc_config.hpp"
#include "../modules/backend/trigger_tower/trigger_tower_config.hpp"
#include "../modules/backend/trigger_tower/trigger_tower_type_config.hpp"
#include "../modules/road_analyzer/road_analyzer_config.hpp"

#include "sector_info.hpp"

#include "../systems/tt_tb_logger.hpp"
#include "../TT_configuration/configuration_defaults.hpp"

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include "prbf_module_address.hpp"

// *****************************************************************************
/*!
 * @brief
 */
class track_trigger_config
{
public:
    typedef sensor_module_address sensor_module_id_t;
    typedef std::map<sensor_module_id_t, sensor_module_config> sensor_module_table_t;
    typedef unsigned int dtc_id_t;
    typedef std::map<dtc_id_t, dtc_config> dtc_table_t;
    typedef unsigned int tower_id_t;
    typedef std::map<tower_id_t, trigger_tower_config> tower_table_t;
//    typedef std::map<unsigned int, sector_info*> sector_table_t;
    typedef std::map<sensor_module_id_t, sector_info*> sector_assign_table_t;

    static const unsigned int sector_start_id = 0;

    unsigned int LHC_clock_period_ns;
    unsigned int hit_FIFO_size;

    hit_generator_config hit_generator;
    sensor_module_type_config cbc_sensor_module;
    sensor_module_type_config mpa_sensor_module;

    dtc_type_config dtc;
    trigger_tower_type_config trigger_tower;

    road_analyzer_config road_analyzer;

    sensor_module_table_t sensor_modules;
    dtc_table_t dtcs;
    tower_table_t trigger_towers;
//    sector_table_t sectors;
    sector_assign_table_t sector_assignments;

    track_trigger_config();
    ~track_trigger_config();

    void set_LHC_clock_period_ns(unsigned int LHC_clock_period_ns);
    void set_hit_FIFO_size(unsigned int hit_FIFO_size);

    void add_sensor_module(const sensor_module_config& new_sensor_module, const unsigned int dtc_id);
    void add_dtc(const dtc_config& new_dtc, const unsigned int tower_id, const unsigned int DO_id);
    void add_trigger_tower(const trigger_tower_config& new_trigger_tower);

    int read_track_trigger_config(const std::string& file_base, const std::string& sector_file_name);
    int read_module_file(const std::string& file_base);
    int read_dtc_file(const std::string& file_base);
    int read_tower_file(const std::string& file_base);
//    int read_sector_file(const std::string& file_name);
    void update_layer_lookup_tables();

    std::vector<sensor_module_address> get_module_addresses() const;
    std::vector<chip_address> get_chip_addresses() const;
    std::vector<trigger_tower_address> get_trigger_tower_addresses() const;
    prbf_module_address get_prbf_address(const sensor_module_address& module_address) const;

    bool find_module_in_dtcs(const sensor_module_address& module_address, unsigned int& dtc_id, unsigned int& relative_module) const;
    bool find_dtc_in_towers(unsigned int dtc_id, unsigned int& trigger_tower, unsigned int& relative_prb, unsigned int& relative_dtc) const;
};
