/*!
 * @file hit_file.hpp
 * @author Christian Amstutz
 * @date June 25, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <queue>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "hit.hpp"
#include "hit_value.hpp"
#include "hit_value_cbc.hpp"
#include "hit_value_mpa.hpp"

class hit_file
{
public:
    static const unsigned int address_length_min = 7;
    static const unsigned int address_length_max = 8;
    // the positions are indicated by the minimum position they can start
    static const unsigned int layer_pos = 0;
    static const unsigned int phi_pos = 1;
    static const unsigned int z_pos = 3;
    static const unsigned int chip_number_pos = 5;

    hit_file();
    ~hit_file();

    bool open(const std::string& filenname);
    void close();
    bool file_ready();
    bool data_ready();

    bool get_next_hit(hit*& return_hit);

    void write_old_format(const std::string& filename);

private:
    bool file_ready_flag;
    std::ifstream file_handler;
    std::string new_line;
    bool new_line_processed;
    unsigned int last_bunch_crossing;

    void read_file();
    bool parse_line(const std::string& line);

    std::queue<hit*> hit_buffer_even;
    std::queue<hit*> hit_buffer_odd;
};
