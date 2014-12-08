/*!
 * @file pattern_bank.cpp
 * @author Christian Amstutz
 * @date December 8, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "pattern_bank.hpp"

// *****************************************************************************
const unsigned int pattern_bank::id_width = 9;
const unsigned int pattern_bank::pattern_width = 4;

// *****************************************************************************
pattern_bank::pattern_bank(const size_t layer_nr) :
        layer_nr(layer_nr)
{
    reverse_tables.resize(layer_nr);

    return;
}

// *****************************************************************************
std::pair<bool, pattern_bank::pattern_t> pattern_bank::find_pattern(
        const pattern_id_t id) const
{
    std::pair<bool, pattern_bank::pattern_t> return_pair(false, pattern_t());

    pattern_memory_t::const_iterator pattern_it = pattern_memory.find(id);
    if (pattern_it != pattern_memory.end())
    {
        return_pair.first = true;
        return_pair.second = pattern_it->second;
    }

    return (return_pair);
}

// *****************************************************************************
std::vector<pattern_bank::pattern_id_t> pattern_bank::find_id(
        const layer_t layer, const element_t& element) const
{
    std::pair<reverse_table_t::const_iterator, reverse_table_t::const_iterator> id_range;
    id_range = reverse_tables[layer].equal_range(element);

    std::vector<pattern_id_t> id_vector;
    reverse_table_t::const_iterator id_it;
    for (id_it = id_range.first; id_it !=id_range.second; ++id_it)
    {
        id_vector.push_back(id_it->second);
    }

    return (id_vector);
}

// *****************************************************************************
std::vector<pattern_bank::pattern_id_t> pattern_bank::find_id(
        const pattern_t& pattern) const
{
    std::map<pattern_id_t, unsigned int> all_id;

    for (unsigned int layer = 0; layer < layer_nr; ++layer)
    {
        std::vector<pattern_bank::pattern_id_t> found_id_layer;
        found_id_layer = find_id(layer, pattern[layer]);
        for (std::vector<pattern_bank::pattern_id_t>::const_iterator id_it = found_id_layer.begin();
             id_it != found_id_layer.end();
             ++id_it)
        {
            all_id[*id_it] = all_id[*id_it]+1;
        }
    }

    std::vector<pattern_id_t> id_vector;
    for (std::map<pattern_id_t, unsigned int>::const_iterator id_it = all_id.begin();
         id_it != all_id.end();
         ++id_it)
    {
        if (id_it->second == layer_nr)
        {
          id_vector.push_back(id_it->first);
        }
    }

    return (id_vector);
}

// *****************************************************************************
size_t pattern_bank::get_pattern_nr() const
{
    return (pattern_memory.size());
}

// *****************************************************************************
void pattern_bank::print_pattern_bank() const
{
    std::cout << std::endl << "Pattern Bank:" << std::endl;

    pattern_memory_t::const_iterator pattern_it = pattern_memory.begin();
    for (; pattern_it != pattern_memory.end(); ++pattern_it)
    {
        std::cout << pattern_it->first << ": ";
        std::cout << pattern_it->second[0];
        for (unsigned int layer = 1; layer < layer_nr; ++layer)
        {
             std::cout << ", " << pattern_it->second[layer];
        }
        std::cout << std::endl;
    }

    return;
}

// *****************************************************************************
void pattern_bank::generate_text_file(const std::string& filename) const
{
    std::ofstream file(filename.c_str());
    file << std::setfill('0');

    pattern_memory_t::const_iterator pattern_it = pattern_memory.begin();
    for (; pattern_it != pattern_memory.end(); ++pattern_it)
    {
        file << std::setw(id_width) << std::hex << pattern_it->first << " ";
        file << std::setw(pattern_width) << std::hex << pattern_it->second[0];
        for (unsigned int layer = 1; layer < layer_nr; ++layer)
        {
             file << " " << std::setw(pattern_width) << std::hex << pattern_it->second[layer];
        }
        file << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::generate_binary_file(const std::string& filename) const
{
    std::ofstream file(filename.c_str(), std::ios::binary | std::ios::trunc | std::ios::out);

    file.write(reinterpret_cast<const char*>(&layer_nr), sizeof(layer_nr));
    pattern_memory_t::const_iterator pattern_it = pattern_memory.begin();
    for (; pattern_it != pattern_memory.end(); ++pattern_it)
    {
        file.write(reinterpret_cast<const char*>(&(pattern_it->first)), sizeof(pattern_id_t));
        for (unsigned int layer = 0; layer < layer_nr; ++layer)
        {
             file.write(reinterpret_cast<const char*>(&(pattern_it->second[layer])), sizeof(element_t));
        }
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::import_text_file(const std::string& filename)
{
    std::ifstream file(filename.c_str(), std::ios::in);
    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);
        unsigned int layer_cnt = 0;
        bool last_blank = true;
        for (unsigned int i = 0; i < line.length(); ++i)
        {
            if (line[i] == ' ')
            {
                if (last_blank == false)
                {
                    ++layer_cnt;
                }
                last_blank = true;
            }
            else
            {
                last_blank = false;
            }
        }
        if (line[line.length()-1] == ' ')
        {
            --layer_cnt;
        }
        file.seekg(0);

        if (layer_cnt == layer_nr)
        {
            pattern_memory.clear();

            pattern_t new_pattern;
            new_pattern.resize(layer_cnt);
            pattern_id_t id;
            while(file >> std::hex >> id)
            {
                for (unsigned int layer = 0; layer < layer_nr; ++layer)
                {
                    element_t new_element;
                    file >> std::hex >> new_element;
                    new_pattern[layer] = new_element;
                }
                insert_pattern(id, new_pattern);
            }
        }
        else
        {
            std::cerr << "Error reading text pattern file - layer number does not match" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error reading text pattern file : " << filename << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::import_binary_file(const std::string& filename)
{
    std::ifstream file(filename.c_str(), std::ios::binary | std::ios::in);
    if (file.is_open())
    {
        unsigned int layer;
        file.read(reinterpret_cast<char*>(&layer), sizeof(layer_nr));
        if (layer == layer_nr)
        {
            pattern_memory.clear();

            pattern_t new_pattern;
            new_pattern.resize(layer);
            pattern_id_t id;
            while(file.read(reinterpret_cast<char*>(&id), sizeof(pattern_id_t)))
            {
                for (layer = 0; layer < layer_nr; ++layer)
                {
                    element_t new_element;
                    file.read(reinterpret_cast<char*>(&new_element), sizeof(element_t));
                    new_pattern[layer] = new_element;
                }
                insert_pattern(id,new_pattern);
            }
        }
        else
        {
            std::cerr << "Error reading binary pattern file - layer number does not match" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error reading binary pattern file" << filename << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::insert_pattern(const pattern_id_t id,
        const pattern_t& pattern)
{
    if (pattern.size() == layer_nr)
    {
        pattern_memory.insert(pattern_pair_t(id, pattern));

        for (unsigned int layer = 0; layer < layer_nr; ++layer)
        {
            reverse_pair_t element(pattern[layer], id);
            reverse_tables[layer].insert(element);
        }
    }
    else
    {
        std::cerr << "Pattern Bank: Layers of inserted pattern do not match."
                  << std::endl;
    }

    return;
}

// *****************************************************************************
void pattern_bank::print_reverse_tables()
{
    std::cout << "Reverse Tables:" << std::endl;
    for (unsigned int layer = 0; layer < layer_nr; ++layer)
    {
        std::cout << "Size (" << layer << "): " << reverse_tables[layer].size() << std::endl;
        reverse_table_t::iterator rev_element = reverse_tables[layer].begin();
        for(;rev_element != reverse_tables[layer].end(); ++rev_element)
        {
            std::cout << rev_element->first << "->" << rev_element->second << std::endl;
        }
        std::cout << std::endl;
    }
}
