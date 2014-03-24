/*!
 * @file data_concentrator.hpp
 * @author Christian Amstutz
 * @date Mar 24, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map.hpp"
#include "../lib/systemc_helpers/nbits.hpp"

#include "TT_configuration.hpp"
#include "data_representations/fe_out_data.hpp"
#include "data_representations/dc_out_word.hpp"

/*!
 * @brief
 */
class data_concentrator : public sc_module
{
public:
    typedef sc_bv<DC_OUTPUT_WIDTH> dc_out_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_map_square<sc_in<fe_out_data> > fe_stub_in;
    sc_out<dc_out_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<sc_uint<NBITS(NR_DC_WINDOW_CYCLES-1)> > clock_phase;
    sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES> output_buffer;

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
    std::vector<dc_out_word> stub_buffer;

    void create_output_buffer();
};
