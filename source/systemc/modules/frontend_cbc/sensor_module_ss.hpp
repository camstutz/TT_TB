/*!
 * @file sensor_module_ss.hpp
 * @author Christian Amstutz
 * @date Apr 24, 2014
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

#include "../../data_formats/stub_sb.hpp"
#include "../../systems/TT_configuration.hpp"

#include "front_end_chip.hpp"
#include "data_concentrator.hpp"

/*!
 * @brief SystemC which represents one sensor module of the detector.
 * Combines the front end chips and the data concentrator.
 */
class sensor_module_ss : public sc_module
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
    sensor_module_ss(const sc_module_name _name);
    SC_HAS_PROCESS(sensor_module_ss);

};
