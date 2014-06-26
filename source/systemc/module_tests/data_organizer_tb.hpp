/*!
 * @file data_organizer_tb.hpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
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

#include "../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../systems/TT_configuration.hpp"
#include "../modules/backend/data_organizer/data_organizer.hpp"
#include "../data_formats/do_out_data.hpp"

/*!
 * @brief
 */
class data_organizer_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;
    sc_map_linear<sc_signal<sc_bv<DC_OUTPUT_WIDTH> > > fe_streams;
    sc_map_square<sc_signal<do_out_data> > do_output;

    // ----- Process Declarations ----------------------------------------------
    void write_stream();
    void print_output();

    void test_proc();

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

private:
    std::ostringstream log_buffer;
};
