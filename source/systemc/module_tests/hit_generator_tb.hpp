/*!
 * @file hit_generator_test.hpp
 * @author Christian
 * @date August 20, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../systems/TT_configuration.hpp"
#include "../TT_configuration/track_trigger_config.hpp"
#include "../modules/hit_generator/hit_generator.hpp"
#include "../modules/frontend/sensor_module_address.hpp"

#include "sc_map.hpp"

#include "systemc.h"

#include <vector>
#include <sstream>

/*!
 * @brief
 */
class hit_generator_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_list<sensor_module_address, sc_fifo<stub> > hit_signals;

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
    hit_generator_config configuration;
    std::ostringstream log_buffer;

};
