/*!
 * @file sensor_module.hpp
 * @author Christian Amstutz
 * @date August 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../frontend_chip/frontend_chip.hpp"
#include "../data_concentrator/data_concentrator.hpp"
#include "../gbt/gbt.hpp"

#include "sensor_module_config.hpp"

#include "sc_map.hpp"

#include <systemc.h>

// *****************************************************************************
/*!
 * @brief SystemC module which represents one sensor module of the detector.
 * Combines the front end chips and the data concentrator.
 */

class sensor_module : public sc_module
{
public:

    typedef typename frontend_chip::output_stub_t fe_stub_t;
    typedef typename data_concentrator::output_t cic_out_t;
    typedef typename gbt::output_t gbt_link_t;

    const sensor_module_config configuration;

    const unsigned int sides;
    const unsigned int fe_chips_per_side;
    const unsigned int hits_per_fe_chip;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_square<sc_fifo_in<fe_stub_t> > stub_inputs;
    sc_out<gbt_link_t> gbt_link;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_cube<sc_buffer<bool> > fe_data_valid_signals;
    sc_map_cube<sc_buffer<fe_stub_t> > fe_out_signals;
    sc_map_linear<sc_buffer<cic_out_t> > cic_out_signals;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_square<frontend_chip> front_end_chips;
    sc_map_linear<data_concentrator> concentrators;
    gbt gbt_unit;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    sensor_module(const sc_module_name _name, const sensor_module_config& configuration);
};
