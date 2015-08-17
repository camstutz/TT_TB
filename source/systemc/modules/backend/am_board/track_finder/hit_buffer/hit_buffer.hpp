/*!
 * @file hit_buffer.hpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "hit_buffer_lookup_ctrl.hpp"
#include "hit_buffer_output_ctrl.hpp"
#include "hit_buffer_write_ctrl.hpp"

#include "hit_buffer_config.hpp"
#include "../../../../../systems/TT_configuration.hpp"

#include "sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include <systemc.h>

#include <queue>
#include <vector>
#include <list>
#include <utility>

/*!
 * @brief
 */
class hit_buffer : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;
    typedef simple_stream_protocol<substrip_t> substrip_stream;

    typedef std::pair<bool, std::list<substrip_t> > superstrip_table_element_t;
    typedef std::map<superstrip_t, superstrip_table_element_t> superstrip_table_t;
    typedef std::vector<superstrip_table_t> event_set_t;

    const unsigned int layer_nr;

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

    std::queue<event_set_t> hit_storage;

    // ----- Process Declarations ----------------------------------------------
    void initialize_event();
    void write_buffer();
    void search_hits();
    void memory_monitor();

    // ----- Other Method Declarations -----------------------------------------
    void print_superstrip_table(superstrip_table_t table);

    // ----- Module Instantiations ---------------------------------------------
    hit_buffer_write_ctrl write_controller;
    hit_buffer_lookup_ctrl lookup_controller;
    hit_buffer_output_ctrl output_controller;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_buffer(const sc_module_name _name, const hit_buffer_config configuration);
    SC_HAS_PROCESS(hit_buffer);
    ~hit_buffer();

private:
    unsigned int max_eventbuffers;
};
