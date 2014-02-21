/*!
 * @file data_organizer_tb.hpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
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

#include "../lib/systemc_helpers/sc_map/sc_map_square.hpp"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/data_organizer.hpp"
#include "../systemc/stub_ext.hpp"
#include "../systemc/do_out_data.hpp"

/*!
 * @brief
 */
class data_organizer_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;
    sc_map_linear<sc_signal<do_out_data> > fe_signals;
    sc_signal<sc_bv<DC_OUTPUT_WIDTH> > dc_output;

    // ----- Process Declarations ----------------------------------------------
    void write_stream();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    data_organizer dut_data_organizer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer_tb(sc_module_name _name);
    SC_HAS_PROCESS(data_organizer_tb);
    ~data_organizer_tb();
    void end_of_elaboration();

private:
    std::ostringstream log_buffer;
};
