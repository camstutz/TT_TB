/*!
 * @file sensor_module_cbc.hpp
 * @author Christian Amstutz
 * @date December 15, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"

#include "frontend_chip_cbc.hpp"
#include "data_concentrator_cbc.hpp"

/*!
 * @brief SystemC which represents one sensor module of the detector.
 * Combines the front end chips and the data concentrator.
 */
class sensor_module_cbc : public sc_module
{
public:

    typedef frontend_chip_cbc::input_stub_t fe_stub_t;
    typedef data_concentrator_cbc::output_stream_t dc_out_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_fifo_in<fe_stub_t> > stub_inputs;
    sc_out<dc_out_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_square<sc_signal<bool> > data_valid_signals;
    sc_map_square<sc_signal<fe_stub_t> > fe_out_signals;

    // ----- Process Declarations ----------------------------------------------

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_map_linear<frontend_chip_cbc> front_end_chips;
    data_concentrator_cbc dataConcentrator;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    sensor_module_cbc(const sc_module_name _name);
    SC_HAS_PROCESS(sensor_module_cbc);

};
