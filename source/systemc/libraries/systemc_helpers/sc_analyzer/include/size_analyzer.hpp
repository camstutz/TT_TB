/*!
 * @file size_analyzer.hpp
 * @author Christian Amstutz
 * @date April 15, 2016
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2016 by Christian Amstutz
 */

#include <map>
#include <string>
#include <sstream>
#include <iomanip>

#include <systemc.h>

#pragma once

class size_analyzer
{
    std::map<std::string, unsigned int> sc_map_counter;
    unsigned int total_sc_map  = 0;

    std::map<std::string, unsigned int> element_counter;
    unsigned int total_elements = 0;

public:
    void add_element(sc_object* systemc_element)
    {
        std::string element_kind = systemc_element->kind();
        std::map<std::string, unsigned int>::iterator specific_counter = element_counter.find(element_kind);
        if ( specific_counter != element_counter.end() )
        {
            (specific_counter->second)++;
        }
        else
        {
            element_counter[element_kind] = 1;
        }

        ++total_elements;

        return;
    }

    void add_sc_map()
    {
        ++total_sc_map;
    }

    void add_sc_map(const char* kind)
    {
        std::map<std::string, unsigned int>::iterator specific_counter = sc_map_counter.find(kind);
        if ( specific_counter != sc_map_counter.end() )
        {
            (specific_counter->second)++;
        }
        else
        {
            sc_map_counter[kind] = 1;
        }

        return;
    }

    std::string get_result()
    {
        std::stringstream output_string;

        output_string << "***************************************" << std::endl;
        output_string << total_sc_map << " sc_map objects by " << std::endl;
        for(std::map<std::string, unsigned int>::iterator one_cnt = sc_map_counter.begin();
            one_cnt != sc_map_counter.end();
            ++one_cnt)
        {
            output_string << "  " <<  std::setw(12) << one_cnt->first << ": " << one_cnt->second << std::endl;
        }

        output_string << "***************************************" << std::endl;
        output_string << total_elements << " elements within sc_map containers" << std::endl;
        for(std::map<std::string, unsigned int>::iterator one_cnt = element_counter.begin();
            one_cnt != element_counter.end();
            ++one_cnt)
        {
            output_string << "  " <<  std::setw(12) << one_cnt->first << ": " << one_cnt->second << std::endl;
        }
        output_string << "***************************************" << std::endl;

        return output_string.str();
    }

    void print_report()
    {
        std::cout << get_result();

        return;
    }
};

//extern size_analyzer simulation_size;
