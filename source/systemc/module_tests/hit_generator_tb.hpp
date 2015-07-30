/*!
 * @file hit_generator_test.hpp
 * @author Christian
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <sstream>

#include "systemc.h"

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../systems/TT_configuration.hpp"
#include "../TT_configuration/track_trigger_config.hpp"
#include "../modules/hit_generator/hit_generator.hpp"

/*!
 * @brief
 */
class hit_generator_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_4d<sc_fifo<hit_generator::mpa_stub_t> > hit_signals_mpa;
    sc_map_4d<sc_fifo<hit_generator::cbc_stub_t> > hit_signals_cbc;

    sc_signal<unsigned int> hit_cnt_signal;

    // ----- Process Declarations ----------------------------------------------
    void check_output();
    void check_hit_counter();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    hit_generator dut_hit_generator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_generator_tb(const sc_module_name _name, const track_trigger_config configuration);
    SC_HAS_PROCESS(hit_generator_tb);
    ~hit_generator_tb();

private:
    std::ostringstream log_buffer;

};
