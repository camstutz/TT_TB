/*!
 * @file road_processor.hpp
 * @author Christian Amstutz
 * @date November 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "simple_stream_protocol.hpp"

#include "am_ctrl_exp_config.hpp"

#define VALUE_EVENT 0

/*!
 * @brief
 */
class road_processor : public sc_module
{
public:
    typedef simple_stream_protocol<road_t> road_stream;
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<road_stream> road_input;
    sc_out<road_t> road_lookup;
    sc_map_linear<sc_in<superstrip_t> > found_pattern;
    sc_map_linear<sc_out<superstrip_stream> > superstrip_lookup;
    sc_map_linear<sc_in<hit_t> > hit_lookup_result;
    sc_map_linear<sc_out<hit_t> > hit_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_fifo<road_stream> command_buffer;
    sc_map_linear<sc_signal<hit_t> > filtered_hits;

    // ----- Process Declarations ----------------------------------------------
    void process_incoming_roads();
    void lookup_superstrips();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    road_processor(const sc_module_name _name);
    SC_HAS_PROCESS(road_processor);
};
