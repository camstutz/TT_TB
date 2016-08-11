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
    for (reverse_table_t::const_iterator id_it = id_range.first;
         id_it !=id_range.second;
         ++id_it)
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
std::string pattern_bank::print_pattern_bank() const
{
    std::stringstream output_stream;

    output_stream << "Pattern Bank (" << pattern_memory.size() <<"):" << std::endl;

    pattern_memory_t::const_iterator pattern_it = pattern_memory.begin();
    for (; pattern_it != pattern_memory.end(); ++pattern_it)
    {
        output_stream << pattern_it->first << ": ";
        output_stream << pattern_it->second[0];
        for (unsigned int layer = 1; layer < layer_nr; ++layer)
        {
             output_stream << ", " << pattern_it->second[layer];
        }
        output_stream << std::endl;
    }

    return output_stream.str();
}

// *****************************************************************************
void pattern_bank::clear()
{
    pattern_memory.clear();
    reverse_lookup_collection_t::iterator rev_table_it = reverse_tables.begin();
    for(; rev_table_it != reverse_tables.end(); ++rev_table_it)
    {
        rev_table_it->clear();
    }

    return;
}

// *****************************************************************************
void pattern_bank::generate_patterns_straight(const unsigned int pattern_nr)
{
    for (unsigned int i = 0; i <  pattern_nr; ++i)
    {
        pattern_t new_pattern;
        new_pattern.resize(layer_nr);
        pattern_t::iterator layer_it = new_pattern.begin();
        for (; layer_it != new_pattern.end(); ++layer_it)
        {
            *layer_it = i;
        }
        insert_pattern(i, new_pattern);
    }

    return;
}

// *****************************************************************************
void pattern_bank::generate_patterns_slight_tilt(const unsigned int pattern_nr)
{
    for (unsigned int i = 0; i <  pattern_nr; ++i)
    {
        std::vector<pattern_t> new_patterns;
        new_patterns.resize(3);

        for (unsigned int layer = 0; layer < layer_nr; ++layer)
        {
            new_patterns[0].push_back(i);
            if (layer < layer_nr/2)
            {
                new_patterns[1].push_back(i);
                new_patterns[2].push_back(i);
            }
            else
            {
                if (i > 0)
                {
                    new_patterns[1].push_back(i-1);
                }
                if (i < pattern_nr-1)
                {
                    new_patterns[2].push_back(i+1);
                }
            }
        }

        unsigned int j = 0;
        for (std::vector<pattern_t>::iterator pattern_it = new_patterns.begin();
             pattern_it != new_patterns.end();
             ++pattern_it)
        {
            insert_pattern(3*i+j, *pattern_it);

            ++j;
        }
    }

    return;
}

// *****************************************************************************
void pattern_bank::store_text_file(const std::string& filename) const
{
    std::ofstream file(filename.c_str());
    file << std::setfill('0');

    pattern_memory_t::const_iterator pattern_it = pattern_memory.begin();
    for (; pattern_it != pattern_memory.end(); ++pattern_it)
    {
        for (unsigned int layer = 0; layer < layer_nr; ++layer)
        {
            CMSPatternLayer mp;
            mp.setIntValue(pattern_it->second[layer]);
            file << mp.toString() << " - ";
        }
        file << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::store_text_binary_file(const std::string& filename) const
{
    std::ofstream file(filename.c_str());

    pattern_memory_t::const_iterator pattern_it = pattern_memory.begin();
    for (; pattern_it != pattern_memory.end(); ++pattern_it)
    {
        for (unsigned int layer = 0; layer < layer_nr; ++layer)
        {
            CMSPatternLayer mp;
            mp.setIntValue(pattern_it->second[layer]);
            file << mp.toStringBinary() << " - ";
        }
        file << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::store_binary_file(const std::string& filename) const
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
//void pattern_bank::load_text_file(const std::string& filename)
//{
//    std::ifstream file(filename.c_str(), std::ios::in);
//    if (file.is_open())
//    {
//        std::string line;
//        std::getline(file, line);
//        unsigned int layer_cnt = 0;
//        bool last_blank = true;
//        for (unsigned int i = 0; i < line.length(); ++i)
//        {
//            if (line[i] == ' ')
//            {
//                if (last_blank == false)
//                {
//                    ++layer_cnt;
//                }
//                last_blank = true;
//            }
//            else
//            {
//                last_blank = false;
//            }
//        }
//        if (line[line.length()-1] == ' ')
//        {
//            --layer_cnt;
//        }
//        file.seekg(0);
//
//        if (layer_cnt == layer_nr)
//        {
//            pattern_memory.clear();
//
//            pattern_t new_pattern;
//            new_pattern.resize(layer_cnt);
//            pattern_id_t id;
//            while(file >> std::hex >> id)
//            {
//                for (unsigned int layer = 0; layer < layer_nr; ++layer)
//                {
//                    element_t new_element;
//                    file >> std::hex >> new_element;
//                    new_pattern[layer] = new_element;
//                }
//                insert_pattern(id, new_pattern);
//            }
//        }
//        else
//        {
//            std::cerr << "Error reading text pattern file - layer number does not match" << std::endl;
//        }
//    }
//    else
//    {
//        std::cerr << "Error reading text pattern file : " << filename << std::endl;
//    }
//
//    file.close();
//
//    return;
//}

// *****************************************************************************
void pattern_bank::load_text_binary_file(const std::string& filename)
{
    // Analyze File format
    size_t file_layer_nr = 0;
    unsigned int nr_dc_bits = 0;
    std::ifstream file(filename.c_str(), std::ios::in);
    if (file.is_open())
    {
        std::string line = "";
        while (std::getline(file, line))
        {
            // Line starts with number
            if ((line[0] >= '0') & (line[0] <= '9') )
            {
                file_layer_nr = std::count(line.begin(), line.end(), '-');

                size_t start_dc = line.find('(', 0);
                size_t end_dc = line.find(')', 0);
                if (start_dc == std::string::npos)
                {
                    nr_dc_bits = 0;
                }
                else
                {
                    nr_dc_bits = end_dc-start_dc-1;
                }

                break;
            }
        }

        if (file_layer_nr != layer_nr)
        {
            std::cerr << "Layers of pattern bank " << filename << " does not fit with model." << std::endl;

            return;
        }

        file.seekg(0);
        while (std::getline(file, line))
        {
            // Line starts with number
            if ((line[0] >= '0') & (line[0] <= '9') )
            {
                pattern_t pattern;
                pattern.resize(layer_nr);
                std::stringstream line_stream(line);

                for (unsigned int layer = 0; layer < layer_nr; ++layer)
                {
                    element_t pattern_element;
                    char dc_bits[5];
                    char dump[5];
                    line_stream >> pattern_element;
                    line_stream.get(dump, 3);
                    line_stream.get(dc_bits, nr_dc_bits+1);
                    line_stream.get(dump, 4);

                    pattern[layer] = pattern_element;
                }
                insert_pattern(pattern);
            }
        }
    }
    else
    {
        std::cerr << "Error opening text binary pattern file: " << filename << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::load_binary_file(const std::string& filename)
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
            std::cerr << "Error reading binary pattern file - layer number does not match." << std::endl;
        }
    }
    else
    {
        std::cerr << "Error reading binary pattern file: " << filename << std::endl;
    }

    file.close();

    return;
}

// *****************************************************************************
void pattern_bank::load_CMSSW_patterns(const std::string& filename)
{
    SectorTree sector_tree;

    std::ifstream pattern_file(filename.c_str());
    boost::iostreams::filtering_stream<boost::iostreams::input> gzip_filter;
    gzip_filter.push(boost::iostreams::gzip_decompressor());
    // We try to read a compressed file
    try
    {
        gzip_filter.push(pattern_file);
        boost::archive::text_iarchive file_archive(gzip_filter);

        //file_archive.template register_type<SectorTree>();
        file_archive.template register_type<Sector>();

        file_archive >> sector_tree;
        std::cout << "compressed pattern file read." << std::endl;
    }
    catch (boost::iostreams::gzip_error& e)
    {
        // File is not compressed->read it without decompression
        if(e.error()==4)
        {
         std::ifstream uncomp_pattern_file(filename.c_str());
         boost::archive::text_iarchive file_archive(uncomp_pattern_file);
         file_archive >> sector_tree;
         std::cout << "uncompressed pattern file read." << std::endl;
        }
    }

    vector<Sector*> sectors = sector_tree.getAllSectors();
    for(unsigned int i=0; i < sectors.size(); ++i)
    {
        Sector* mySector = sectors[i];
        vector<GradedPattern*> patterns = mySector->getPatternTree()->getLDPatterns();
        for(unsigned int j=0; j<patterns.size(); ++j)
        {
            Pattern* p = patterns[j];
            for(int k=0;k<p->getNbLayers();k++)
            {
                PatternLayer* mp = p->getLayerStrip(k);
                cout<<((CMSPatternLayer*)mp)->toStringBinary()<<" - ";
            }
            cout<<endl;
        }
    }

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
void pattern_bank::insert_pattern(const pattern_t& pattern)
{
    unsigned int pattern_cnt = pattern_memory.size();

    insert_pattern(pattern_cnt, pattern);

    return;
}

// *****************************************************************************
std::string pattern_bank::print_reverse_tables()
{
    std::stringstream output_stream;

    output_stream << "Reverse Tables:" << std::endl;
    for (unsigned int layer = 0; layer < layer_nr; ++layer)
    {
        output_stream << "Size (" << layer << "): " << reverse_tables[layer].size() << std::endl;
        for(reverse_table_t::iterator rev_element = reverse_tables[layer].begin();
            rev_element != reverse_tables[layer].end();
            ++rev_element)
        {
            output_stream << rev_element->first << "->" << rev_element->second << std::endl;
        }
        output_stream << std::endl;
    }

    return output_stream.str();
}
