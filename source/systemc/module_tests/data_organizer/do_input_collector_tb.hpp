/*!
 * @file do_input_collector_tb.hpp
 * @author Christian Amstutz
 * @date April 16, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/data_organizer/do_input_collector.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class do_input_collector_tb : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<do_input_collector::input_t> > dtc_input_sig;
    sc_fifo<do_input_collector::output_t> stub_output_fifo;

    // ----- Process Declarations ----------------------------------------------
    void write_frames();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    do_input_collector dut_do_input_collector;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    do_input_collector_tb(sc_module_name _name);
    SC_HAS_PROCESS(do_input_collector_tb);
    ~do_input_collector_tb();

private:
    std::ostringstream log_buffer;
};
