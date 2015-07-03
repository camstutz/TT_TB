/*!
 * @file road_processor.hpp
 * @author Christian Amstutz
 * @date March 31, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"
#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include "road_processor_config.hpp"
#include "../../../../../systems/TT_configuration.hpp"

//#define VALUE_EVENT 0

/*!
 * @brief
 */
class road_processor : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;
    typedef simple_stream_protocol<road_t> road_stream;
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;

    const unsigned int layer_nr;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<road_stream> road_input;
    sc_out<road_t> road_lookup;
    sc_map_linear<sc_in<superstrip_t> > found_pattern;
    sc_map_linear<sc_out<superstrip_stream> > superstrip_lookup;
    sc_map_linear<sc_in<hit_stream> > hit_lookup_result;
    sc_map_linear<sc_out<hit_stream> > hit_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_fifo<road_stream> command_buffer;
    sc_buffer<road_stream> command_buffer_write_sig;
    sc_buffer<road_stream> command_buffer_delayed_sig;

    // ----- Process Declarations ----------------------------------------------
    void process_incoming_roads();
    void write_FIFO();
    void lookup_superstrips();
    void output_result();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_delay_signal<road_stream, PATTERN_MEMORY_LATENCY> pattern_mem_delay_compensation;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    road_processor(const sc_module_name _name, const road_processor_config configuration);
    SC_HAS_PROCESS(road_processor);
};
