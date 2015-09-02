/*!
 * @file track_trigger_config.cpp
 * @author Christian Amstutz
 * @date September 2, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "track_trigger_config.hpp"

// *****************************************************************************
track_trigger_config::track_trigger_config()
{
    set_LHC_clock_period_ns(LHC_CLOCK_PERIOD_NS_DEFAULT);
    set_hit_FIFO_size(HIT_FIFO_SIZE_DEFAULT);

    return;
}

// *****************************************************************************
void track_trigger_config::set_LHC_clock_period_ns(unsigned int LHC_clock_period_ns)
{
    this->LHC_clock_period_ns = LHC_clock_period_ns;
    hit_generator.set_LHC_clock_period_ns(LHC_clock_period_ns);

    return;
}

// *****************************************************************************
void track_trigger_config::set_hit_FIFO_size(unsigned int hit_FIFO_size)
{
    this->hit_FIFO_size = hit_FIFO_size;

    return;
}

// *****************************************************************************
void track_trigger_config::add_sensor_module(
        const sensor_module_address& address,
        const sensor_module_type_config& type)
{
    sensor_module_config module;
    module.address = address;
    module.type = type;

    sensor_modules[module.address] = module;

    hit_generator.add_chips(module);

    return;
}

// *****************************************************************************
void track_trigger_config::add_sensor_modules(
        const std::vector<sensor_module_address>& addresses,
        const sensor_module_type_config& type)
{
    for (std::vector<sensor_module_address>::const_iterator address = addresses.begin();
         address != addresses.end();
         ++address)
    {
        add_sensor_module(*address, type);
    }

    return;
}

// *****************************************************************************
void track_trigger_config::add_DTC(const dtc_id_t id,
        const std::vector<sensor_module_address>& sensor_modules)
{
    add_DTC(id, sensor_modules, this->dtc);

    return;
}

// *****************************************************************************
void track_trigger_config::add_DTC(const dtc_id_t id,
        const std::vector<sensor_module_address>& sensor_modules,
        const dtc_type_config& type)
{
    dtc_config new_dtc;
    new_dtc.type = type;
    for (std::vector<sensor_module_address>::const_iterator module = sensor_modules.begin();
         module != sensor_modules.end();
         ++module)
    {
        new_dtc.add_sensor_module(*module);
    }

    dtcs[id] = new_dtc;

    return;
}

// *****************************************************************************
void track_trigger_config::add_DTC(const std::vector<sensor_module_address>&
        sensor_modules)
{
    add_DTC(sensor_modules, this->dtc);

    return;
}

// *****************************************************************************
void track_trigger_config::add_DTC(const std::vector<sensor_module_address>&
        sensor_modules, const dtc_type_config& type)
{
    dtc_id_t id;
    if (!dtcs.empty())
    {
        id = dtcs.rbegin()->first;
        ++id;
    }

    add_DTC(id, sensor_modules, type);

    return;
}

// *****************************************************************************
void track_trigger_config::add_sensor_module(
        const sensor_module_config& new_sensor_module, const unsigned int dtc_id)
{
    sensor_modules[new_sensor_module.address] = new_sensor_module;

    if (dtcs.count(dtc_id) > 0)
    {
        dtcs[dtc_id].add_sensor_module(new_sensor_module.address);
    }
    else
    {
        std::cerr << "Trying to add sensor_module to non existing DTC "
                   << dtc_id <<  std::endl;
    }

    return;
}

// *****************************************************************************
void track_trigger_config::add_dtc(
        const dtc_config& new_dtc, const unsigned int tower_id,
        const unsigned int DO_id)
{
    dtcs[new_dtc.id] = new_dtc;

    if (trigger_towers.count(tower_id) > 0)
    {
        trigger_towers[tower_id].DTC_ids.push_back(new_dtc.id);
        trigger_towers[tower_id].data_organizers[DO_id].add_dtc(new_dtc.id);
    }
    else
    {
        std::cerr << "Trying to add DTC to non existing trigger tower "
                   << tower_id <<  std::endl;
    }

    return;
}

// *****************************************************************************
void track_trigger_config::add_trigger_tower(
        const trigger_tower_config& new_trigger_tower)
{
    trigger_towers[new_trigger_tower.id] = new_trigger_tower;

    return;
}

// *****************************************************************************
int track_trigger_config::read_track_trigger_config(const std::string& file_base)
{
    int error = 0;

    error += read_tower_file(file_base);
    error += read_dtc_file(file_base);
    error += read_module_file(file_base);

    return error;
}

// *****************************************************************************
int track_trigger_config::read_module_file(const std::string& file_base)
{
    std::string file_name(file_base + "_modules.dat");

    std::ifstream struct_file;
    struct_file.open(file_name.c_str());
    if (struct_file.is_open())
    {
        // read all the sensor modules from the file
        std::string fileLine;
        while (std::getline(struct_file, fileLine))
        {
            bool line_valid;
            unsigned int id;
            unsigned int layer;
            unsigned int ladder;
            unsigned int module;
            std::string type;
            unsigned int dtc_id;

            std::stringstream fileLineStream(fileLine);
            fileLineStream >> std::dec >> id
                           >> layer >> ladder >> module
                           >> type >> dtc_id;
            if ( !fileLineStream.fail() )
            {
                line_valid = true;
            }
            else
            {
                line_valid = false;
            }

            // check for valid stub in the read line
            if (line_valid)
            {
                sensor_module_config new_module;
                new_module.id = id;
                new_module.address = sensor_module_address(layer, ladder, module);
                if (type == "PS")
                {
                    new_module.type = mpa_sensor_module;
                }
                else if (type == "2S")
                {
                    new_module.type = cbc_sensor_module;
                }
                else
                {
                    std::cerr << "Unknown type for sensor module." << std::endl;
                }

                add_sensor_module(new_module, dtc_id);
            }
        }

        struct_file.close();
    }
    else
    {
        std::cout << "File with DTC configuration could not be read: "
                  << struct_file << std::endl;
        return 1;
    }

    return 0;
}

// *****************************************************************************
int track_trigger_config::read_dtc_file(const std::string& file_base)
{
    std::string file_name(file_base + "_dtcs.dat");

    std::ifstream struct_file;
    struct_file.open(file_name.c_str());
    if (struct_file.is_open())
    {
        // read all the DTCs from the file
        std::string fileLine;
        while (std::getline(struct_file, fileLine))
        {
            bool line_valid;
            unsigned int id;
            unsigned int trigger_tower_id;
            unsigned int do_id;

            std::stringstream fileLineStream(fileLine);
            fileLineStream >> std::dec >> id >> trigger_tower_id >> do_id;
            if ( !fileLineStream.fail() )
            {
                line_valid = true;
            }
            else
            {
                line_valid = false;
            }

            // check for valid stub in the read line
            if (line_valid)
            {
                dtc_config new_dtc;
                new_dtc.id = id;
                new_dtc.type = dtc;

                add_dtc(new_dtc, trigger_tower_id, do_id);
            }
        }

        struct_file.close();
    }
    else
    {
        std::cout << "File with DTC configuration could not be read: "
                  << struct_file << std::endl;
        return 1;
    }

    return 0;
}

// *****************************************************************************
int track_trigger_config::read_tower_file(const std::string& file_base)
{
    std::string file_name(file_base + "_towers.dat");

    std::ifstream struct_file;
    struct_file.open(file_name.c_str());
    if (struct_file.is_open())
    {
        // read all the trigger towers from the file
        std::string fileLine;
        while (std::getline(struct_file, fileLine))
        {
            bool line_valid;
            unsigned int id;
            unsigned int phi;
            unsigned int z;
            unsigned int DO_count;

            std::stringstream fileLineStream(fileLine);
            fileLineStream >> std::dec >> id >> phi >> z >> DO_count;
            if ( !fileLineStream.fail() )
            {
                line_valid = true;
            }
            else
            {
                line_valid = false;
            }

            // check for valid stub in the read line
            if (line_valid)
            {
                trigger_tower_config new_tower(trigger_tower);
                new_tower.id = id;
                new_tower.address = trigger_tower_address(phi, z);
                for(unsigned int i = 0; i < DO_count; ++i)
                {
                    data_organizer_config new_do;
                    new_do.type = trigger_tower.data_organizer;
                    new_tower.data_organizers.push_back(new_do);
                }

                add_trigger_tower(new_tower);
            }
        }

        struct_file.close();
    }
    else
    {
        std::cout << "File with trigger tower configuration could not be read: "
                  << struct_file << std::endl;
        return 1;
    }

    return 0;
}

// *****************************************************************************
std::vector<sensor_module_address> track_trigger_config::get_module_addresses() const
{
    std::vector<sensor_module_address> module_addresses;
    for (sensor_module_table_t::const_iterator module_config_it = sensor_modules.begin();
         module_config_it != sensor_modules.end();
         module_config_it++)
    {
        module_addresses.push_back(module_config_it->second.address);
    }

    return module_addresses;
}

// *****************************************************************************
std::vector<chip_address> track_trigger_config::get_chip_addresses() const
{
    std::vector<chip_address> chip_addresses;
    for (sensor_module_table_t::const_iterator module_config_it = sensor_modules.begin();
         module_config_it != sensor_modules.end();
         module_config_it++)
    {
        sensor_module_address module_address = module_config_it->second.address;
        std::vector<chip_address> new_chips = module_address.get_chips(module_config_it->second.type);
        chip_addresses.insert(chip_addresses.end(), new_chips.begin(), new_chips.end());
    }

    return chip_addresses;
}

// *****************************************************************************
std::vector<trigger_tower_address> track_trigger_config::get_trigger_tower_addresses() const
{
    std::vector<trigger_tower_address> tower_addresses;
    for (tower_table_t::const_iterator tower_config_it = trigger_towers.begin();
         tower_config_it != trigger_towers.end();
         tower_config_it++)
    {
        tower_addresses.push_back(tower_config_it->second.address);
    }

    return tower_addresses;
}
