/*!
 * @file input_collector_tb.hpp
 * @author Christian Amstutz
 * @date July 1, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../modules/backend/common/input_collector.hpp"
#include "../../modules/backend/common/input_collector_config.hpp"

#include "../../data_formats/sc_pair/sc_pair.hpp"
#include "../../data_formats/prbf/PRBF.hpp"

#include "sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class input_collector_tb : public sc_module
{
public:
    typedef input_collector<PRBF_0, PRBF_1> do_input_collector;

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_map_linear<sc_buffer<do_input_collector::input_t> > dtc_input_sig;
    sc_fifo<typename do_input_collector::output_t> stub_output_fifo;

    // ----- Process Declarations ----------------------------------------------
    void write_frames();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    do_input_collector dut_input_collector;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    input_collector_tb(sc_module_name _name, input_collector_config configuration);
    SC_HAS_PROCESS(input_collector_tb);
    ~input_collector_tb();

private:
    std::ostringstream log_buffer;
};
