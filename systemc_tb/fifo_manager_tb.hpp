/*!
 * @file fifo_manager_tb.hpp
 * @author Christian Amstutz
 * @date Apr 28, 2014
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

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"

#include "../systemc/TT_configuration.hpp"
#include "../systemc/modules/fifo_manager/fifo_manager.hpp"
#include "../systemc/data_representations/do_out_data.hpp"
#include "../systemc/data_representations/fm_out_data.hpp"

/*!
 * @brief
 */
class fifo_manager_tb : public sc_module
{
public:

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bool> rst;

    sc_map_square<sc_signal<do_out_data>> stub_inputs;
    sc_map_square<sc_signal<fm_out_data>> fifo_outputs;

    // ----- Process Declarations ----------------------------------------------
    void generate_input();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    sc_clock LHC_clock;
    fifo_manager dut_fifo_manager;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    fifo_manager_tb(sc_module_name _name);
    SC_HAS_PROCESS(fifo_manager_tb);
    ~fifo_manager_tb();

private:
    std::ostringstream log_buffer;
};
