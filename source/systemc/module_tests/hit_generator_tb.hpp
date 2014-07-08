/*!
 * @file hit_generator_test.hpp
 * @author Christian
 * @date July 8, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <sstream>

#include "systemc.h"

#include "../libraries/systemc_helpers/sc_map/sc_map_4d.hpp"

#include "../systems/TT_configuration.hpp"
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

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    hit_generator dut_hit_generator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    hit_generator_tb(sc_module_name _name);
    SC_HAS_PROCESS(hit_generator_tb);
    ~hit_generator_tb();

private:
    std::ostringstream log_buffer;

};
