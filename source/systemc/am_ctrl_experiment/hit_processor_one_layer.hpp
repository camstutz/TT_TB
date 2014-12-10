/*!
 * @file hit_processor_one_layer.hpp
 * @author Christian Amstutz
 * @date November 17, 2014
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

/*!
 * @brief
 */
class hit_processor_one_layer : public sc_module
{
public:
    typedef simple_stream_protocol<hit_t> hit_stream;
    typedef simple_stream_protocol<hit_t> superstrip_stream;
    typedef simple_stream_protocol<hit_t> substrip_stream;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<hit_stream> hit_input;
    sc_out<superstrip_stream> am_superstrip_out;
    sc_out<superstrip_stream> hitbuf_superstrip_out;
    sc_out<substrip_stream> hitbuf_substrip_out;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------
    void write_outputs();

    // ----- Other Method Declarations -----------------------------------------
    superstrip_t generate_superstrip(hit_t hit);
    superstrip_t generate_substrip(hit_t hit);

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_processor_one_layer(const sc_module_name _name);
    SC_HAS_PROCESS(hit_processor_one_layer);
};