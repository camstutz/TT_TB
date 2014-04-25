/*!
 * @file front_end_chip_tb.hpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <iostream>
#include <sstream>

#include "systemc.h"

#include "../lib/systemc_helpers/sc_map/sc_map_linear.hpp"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/modules/hit_generator/hit_generator.hpp"
#include "../systemc/modules/sensor_module_ss/front_end_chip.hpp"
#include "../systemc/data_representations/fe_out_data.hpp"

/*!
 * @brief
 */
class front_end_chip_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> en_sig;
    sc_fifo<hit_generator::hitgen_stub_t> stub_input_sig;
    sc_map_linear<sc_signal<fe_out_data> > fe_out_signals;

    // ----- Process Declarations ----------------------------------------------
    void generate_stubs();
    void analyse_FE_out();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    front_end_chip dut_front_end_chip;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    front_end_chip_tb(sc_module_name _name);
    SC_HAS_PROCESS(front_end_chip_tb);
    ~front_end_chip_tb();
    void end_of_elaboration();

private:
    std::ostringstream log_buffer;

};
