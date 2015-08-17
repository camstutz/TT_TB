/*!
 * @file track_finder.hpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "hit_processor/hit_processor.hpp"
#include "pattern_bank/pattern_bank.hpp"
#include "am_chip/am_chip.hpp"
#include "hit_buffer/hit_buffer.hpp"
#include "pattern_memory/pattern_memory.hpp"
#include "road_processor/road_processor.hpp"

#include "track_finder_config.hpp"

#include "../simple_stream_protocol.hpp"

#include "sc_map.hpp"

#include <systemc.h>

// *****************************************************************************
/*!
 * @brief
 */
class track_finder : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;
    typedef simple_stream_protocol<superstrip_t> superstrip_stream;
    typedef simple_stream_protocol<substrip_t> substrip_stream;
    typedef simple_stream_protocol<road_t> road_stream;

    const unsigned int layer_nr;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<hit_stream> > hit_input;
    sc_map_linear<sc_out<hit_stream> > hit_output;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_signal<superstrip_stream> > hit_buffer_ss_store_sig;
    sc_map_linear<sc_signal<substrip_stream> > hit_buffer_subs_store_sig;
    sc_map_linear<sc_signal<superstrip_stream> > am_input_sig;
    sc_signal<road_stream> am_output_sig;
    sc_buffer<road_t> pattern_mem_addr_sig;
    sc_map_linear<sc_buffer<superstrip_t> > pattern_mem_out_sig;
    sc_map_linear<sc_signal<superstrip_stream> > hit_search_sig;
    sc_map_linear<sc_signal<hit_stream> > hit_result_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    pattern_bank patterns;
    hit_processor hit_proc;
    hit_buffer temp_hit_buffer;
    am_chip road_lookup;
    pattern_memory pattern_lookup;
    road_processor road_proc;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    track_finder(const sc_module_name _name, const track_finder_config configuration);
};
