/*!
 * @file hit_processor.hpp
 * @author Christian Amstutz
 * @date April 22, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../simple_stream_protocol.hpp"

#include "../../../../../systems/TT_configuration.hpp"
#include "hit_processor_one_layer.hpp"

/*!
 * @brief
 */
class hit_processor : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;
    typedef simple_stream_protocol<hit_t> superstrip_stream;
    typedef simple_stream_protocol<hit_t> substrip_stream;

    static const unsigned int layer_nr;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<hit_stream> > hit_input;
    sc_map_linear<sc_out<superstrip_stream> > am_superstrip_out;
    sc_map_linear<sc_out<superstrip_stream> > hitbuf_superstrip_out;
    sc_map_linear<sc_out<substrip_stream> > hitbuf_substrip_out;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<hit_processor_one_layer> hit_processors;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_processor(const sc_module_name _name);
    SC_HAS_PROCESS(hit_processor);
};
