/*!
 * @file data_concentrator.hpp
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

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map_square.hpp"

#include "TT_configuration.hpp"
#include "nbits.hpp"
#include "stub.hpp"
#include "fe_out_data.hpp"

/*!
 * @brief
 */
class data_concentrator : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_map_square<sc_in<fe_out_data> > fe_stub_in;
    //! todo: think about the data type of dc_out, generic ?
    sc_out<sc_bv<DC_OUTPUT_WIDTH> > dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    //! todo: change width to generic
    sc_signal<sc_uint<3> > clock_phase;

    // ----- Process Declarations ----------------------------------------------
    void advance_clock_phase();
    void read_FE_chips();
    void write_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    data_concentrator(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator);

private:
    //! todo: make long_stub generic, probably an object
    typedef sc_bv<20> long_stub;
    const long_stub empty_slot;
    std::vector<long_stub> stub_buffer;
    sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES> output_buffer;

    void create_output_buffer();
};
