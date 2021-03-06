/*!
 * @file track_trigger_config.cpp
 * @author Christian Amstutz
 * @date September 30, 2015
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
track_trigger_config::~track_trigger_config()
{
    for (sector_table_t::iterator sector_it=sectors.begin();
         sector_it != sectors.end();
         ++sector_it)
    {
        delete sector_it->second;
    }

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
        const sensor_module_config& new_sensor_module, const unsigned int dtc_id)
{
    sensor_modules[new_sensor_module.address] = new_sensor_module;

    hit_generator.add_chips(new_sensor_module);
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
        trigger_towers[tower_id].get_data_organizer(DO_id).add_dtc(new_dtc.id);
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
int track_trigger_config::read_track_trigger_config(const std::string& file_base,
        const std::string& sector_file_name)
{
    int error = 0;

    error += read_sector_file(sector_file_name);
    error += read_tower_file(file_base);
    error += read_dtc_file(file_base);
    error += read_module_file(file_base);

    integrate_configuration();

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

            if (line_valid)
            {
                sensor_module_config new_module;
                new_module.id = id;
                new_module.address = sensor_module_address(layer, ladder, module);
                if (type == "PS")
                {
                    new_module.type = &mpa_sensor_module;
                }
                else if (type == "2S")
                {
                    new_module.type = &cbc_sensor_module;
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
        std::cout << "File with module configuration could not be read: "
                  << file_name << std::endl;
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
                  << file_name << std::endl;
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
                    new_tower.add_do(new_do);
                }

                add_trigger_tower(new_tower);
            }
        }

        struct_file.close();
    }
    else
    {
        std::cout << "File with trigger tower configuration could not be read: "
                  << file_name << std::endl;
        return 1;
    }

    return 0;
}

// *****************************************************************************
int track_trigger_config::read_sector_file(const std::string& file_name)
{
    std::ifstream sector_file;
    sector_file.open(file_name.c_str());
    if (sector_file.is_open())
    {
        std::cout << "Read sectors from: " << file_name << std::endl;

        // read all the trigger towers from the file
        std::string fileLine;
        // read header line and discard it
        std::getline(sector_file, fileLine);

        int sector_id = sector_start_id;
        while (std::getline(sector_file, fileLine))
        {
            if ( !sector_file.fail() )
            {
                std::stringstream lineStream(fileLine);
                std::vector<unsigned int> numbers_in_line;
                std::string cell;
                while (std::getline(lineStream, cell, ','))
                {
                    std::stringstream cell_stream(cell);
                    unsigned int value;
                    cell_stream >> value;
                    numbers_in_line.push_back(value);
                }

                // check if sector contains modules
                if (numbers_in_line.size() > 2)
                {
                    unsigned int sector_eta = numbers_in_line[0];
                    unsigned int sector_phi = numbers_in_line[1];
                    sector_info* sector = new sector_info(sector_id, sector_eta, sector_phi);
                    sectors[sector_id] = sector;

                    // add all modules to the sector
                    for (std::vector<unsigned int>::iterator module_id_it = numbers_in_line.begin()+2;
                         module_id_it != numbers_in_line.end();
                         ++module_id_it)
                    {
                        sensor_module_address module_address = sensor_module_address(*module_id_it);
                        sector_assignments.insert(std::pair<sensor_module_id_t, sector_info*>(module_address, sector));
                        sector->add_modules(module_address);
                    }
                }
            }
            ++sector_id;
        }

        sector_file.close();
    }
    else
    {
        std::cout << "File with sector configuration could not be read: "
                  << file_name << std::endl;
        return 1;
    }

    return 0;
}

// *****************************************************************************
void track_trigger_config::integrate_configuration()
{
    for (tower_table_t::iterator tower_it = trigger_towers.begin();
         tower_it != trigger_towers.end();
         ++tower_it)
    {
        // todo: assign modules to the correct trigger tower sector.

        for (sensor_module_table_t::iterator sensor_mod_it = sensor_modules.begin();
             sensor_mod_it != sensor_modules.end();
             ++sensor_mod_it)
        {
            unsigned int tower_id = tower_it->second.id;
            sensor_module_address global_address = sensor_mod_it->second.address;

            prbf_module_address hw_address = get_prbf_address(tower_id, global_address);
            std::pair<bool, local_module_address> local_pair = sectors.at(tower_id)->get_local_address(global_address);
            local_module_address local_address = local_pair.second;

            tower_it->second.add_layer(sensor_mod_it->second.address.layer);
            tower_it->second.module_lookup.add_module(hw_address, local_address, global_address);
        }
    }

    return;
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

// *****************************************************************************
prbf_module_address track_trigger_config::get_prbf_address(const unsigned int tower_id,
        const sensor_module_address& module_address) const
{
    unsigned int relative_prb = 0;
    unsigned int dtc_id = 0;
    unsigned int relative_dtc = 0;
    unsigned int relative_module = 0;

    find_module_in_dtcs(module_address, dtc_id, relative_module);
    find_dtc_in_tower(tower_id, dtc_id, relative_prb, relative_dtc);

    return prbf_module_address(tower_id, relative_prb, relative_dtc, relative_module);
}

// *****************************************************************************
bool track_trigger_config::find_module_in_dtcs(
        const sensor_module_address& module_address, unsigned int& dtc_id,
        unsigned int& relative_module) const
{
    for (dtc_table_t::const_iterator dtc_it = dtcs.begin(); dtc_it != dtcs.end(); ++dtc_it)
    {
        std::vector<sensor_module_address> dtc_modules = dtc_it->second.get_sensor_modules();
        relative_module = 0;
        for (std::vector<sensor_module_address>::iterator module_it = dtc_modules.begin();
             module_it != dtc_modules.end();
             ++module_it)
        {
            if (*module_it == module_address)
            {
                dtc_id = dtc_it->second.id;
                return true;
            }
            ++relative_module;
        }
    }

    return false;
}

// *****************************************************************************
bool track_trigger_config::find_dtc_in_tower(unsigned int tower_id,
        unsigned int dtc_id, unsigned int& relative_prb,
        unsigned int& relative_dtc) const
{
    try
    {
        trigger_tower_config tower = trigger_towers.at(tower_id);

        trigger_tower_config::data_organizer_table_t DOs = tower.get_data_organizers();

        relative_prb = 0;
        for (trigger_tower_config::data_organizer_table_t::const_iterator DO_it = DOs.begin();
             DO_it != DOs.end();
             ++DO_it)
        {
            data_organizer_config::DTC_table_t DTCs = DO_it->get_dtcs();
            relative_dtc = 0;
            for (data_organizer_config::DTC_table_t::const_iterator dtc_it = DTCs.begin();
                 dtc_it != DTCs.end();
                 ++dtc_it)
            {
                if (dtc_id == *dtc_it)
                {
                     return true;
                }
                ++relative_dtc;
            }
            ++relative_prb;
        }
    }
    catch (const std::out_of_range& oor)
    {
        return false;
    }

    return false;
}
