/*!
 * @file hit_memory.hpp
 * @author Christian Amstutz
 * @date February 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <queue>
#include <vector>
#include <list>
#include <utility>

#include <systemc.h>
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include "../track_finder_config.hpp"
#include "hit_memory_write_ctrl.hpp"
#include "hit_memory_lookup_ctrl.hpp"
#include "hit_memory_output_ctrl.hpp"

/*!
 * @brief
 */
class hit_memory : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;
    typedef simple_stream_protocol<substrip_t> substrip_stream;

    typedef std::pair<bool, std::list<substrip_t> > superstrip_table_element_t;
    typedef std::map<superstrip_t, superstrip_table_element_t> superstrip_table_t;
    typedef std::vector<superstrip_table_t> event_set_t;
    std::queue<event_set_t> hit_storage;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<superstrip_stream> > superstrip_inputs;
    sc_map_linear<sc_in<substrip_stream> > substrip_inputs;
    sc_map_linear<sc_in<superstrip_stream> > superstrip_search;
    sc_map_linear<sc_out<hit_stream> > hit_outputs;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<bool> > process_hits;
    sc_buffer<bool> write_event_begin;
    sc_buffer<bool> write_event_end;
    sc_buffer<bool> transmit_event_begin;

    sc_map_linear<sc_buffer<superstrip_t> > pure_superstrips;
    sc_map_linear<sc_fifo<hit_t> > output_buffer;

    // ----- Process Declarations ----------------------------------------------
    void initialize_event();
    void write_buffer();
    void search_hits();
    void memory_monitor();

    // ----- Other Method Declarations -----------------------------------------
    void print_superstrip_table(superstrip_table_t table);

    // ----- Module Instantiations ---------------------------------------------
    hit_memory_write_ctrl write_controller;
    hit_memory_lookup_ctrl lookup_controller;
    hit_memory_output_ctrl output_controller;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_memory(const sc_module_name _name);
    SC_HAS_PROCESS(hit_memory);
    ~hit_memory();

private:
    unsigned int max_eventbuffers;
};
