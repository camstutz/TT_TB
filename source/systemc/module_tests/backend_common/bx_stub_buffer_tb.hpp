/*!
 * @file bx_stub_buffer_tb.hpp
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

#include "../../modules/backend/common/bx_stub_buffer.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/prbf/PRBF.hpp"

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "systemc.h"

#include <iostream>
#include <sstream>

/*!
 * @brief
 */
class bx_stub_buffer_tb : public sc_module
{
public:
    typedef bx_stub_buffer<PRBF_1> do_stub_buffer;

    // ----- Port Declarations -------------------------------------------------

    // ----- Local Channel Declarations ----------------------------------------
    sc_fifo<do_stub_buffer::input_pair_t> stub_input_fifo;
    sc_buffer<do_stub_buffer::bunch_crossing_t> bunch_crossing_select_sig;
    sc_fifo<do_stub_buffer::output_t> output_fifo;

    // ----- Process Declarations ----------------------------------------------
    void write_stubs();
    void print_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------
    do_stub_buffer dut_do_stub_buffer;

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    bx_stub_buffer_tb(sc_module_name _name);
    SC_HAS_PROCESS(bx_stub_buffer_tb);
    ~bx_stub_buffer_tb();

private:
    std::ostringstream log_buffer;
};
