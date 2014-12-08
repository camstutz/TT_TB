/*!
 * @file pattern_bank.hpp
 * @author Christian Amstutz
 * @date December 8, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

class pattern_bank
{
public:
    typedef size_t layer_t;
    typedef unsigned int pattern_id_t;
    typedef unsigned int element_t;
    typedef std::vector<element_t> pattern_t;

    pattern_bank(const size_t layer_nr);

    std::pair<bool, pattern_bank::pattern_t> find_pattern(const pattern_id_t id) const;
    std::vector<pattern_id_t> find_id(const layer_t layer, const element_t& element) const;
    std::vector<pattern_id_t> find_id(const pattern_t& pattern) const;

    size_t get_pattern_nr() const;
    void print_pattern_bank() const;

    void generate_text_file(const std::string& filename) const;
    void generate_binary_file(const std::string& filename) const;
    void import_text_file(const std::string& filename);
    void import_binary_file(const std::string& filename);

public:
    typedef std::pair<pattern_id_t, pattern_t> pattern_pair_t;
    typedef std::map<pattern_id_t, pattern_t> pattern_memory_t;
    typedef std::pair<element_t, pattern_id_t> reverse_pair_t;
    typedef std::multimap<element_t, pattern_id_t> reverse_table_t;
    typedef std::vector<reverse_table_t> reverse_lookup_collection_t;

    static const unsigned int id_width;
    static const unsigned int pattern_width;
    const size_t layer_nr;
    pattern_memory_t pattern_memory;
    reverse_lookup_collection_t reverse_tables;

    void insert_pattern(const pattern_id_t id, const pattern_t& pattern);
    void print_reverse_tables();
};
