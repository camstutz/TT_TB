/*!
 * @file sensor_module.hpp
 * @author Christian Amstutz
 * @date Mar 18, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "data_representations/stub_sb.hpp"
#include "TT_configuration.hpp"
#include "front_end_chip.hpp"
#include "data_concentrator.hpp"

/*!
 * @brief SystemC which represents one sensor module of the detector.
 * Combines the front end chips and the data concentrator.
 */
class sensor_module : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_fifo_in<fe_out_data::fe_stub_t> > stub_inputs;
    sc_out<sc_bv<DC_OUTPUT_WIDTH> > dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_square<sc_signal<fe_out_data> > fe_out_signals;
    sc_signal<bool> true_sig;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<front_end_chip> front_end_chips;
    data_concentrator dataConcentrator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    sensor_module(const sc_module_name _name);
    SC_HAS_PROCESS(sensor_module);

};
