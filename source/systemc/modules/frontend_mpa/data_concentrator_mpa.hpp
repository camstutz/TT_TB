/*!
 * @file data_concentrator_mpa.hpp
 * @author Christian Amstutz
 * @date June 26, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <utility>

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../libraries/systemc_helpers/nbits.hpp"

#include "../../systems/TT_configuration.hpp"
#include "../../data_formats/fe_mpa_out_data.hpp"
#include "../../data_formats/dc_mpa_out_word.hpp"

/*!
 * @brief
 */
class data_concentrator_mpa : public sc_module
{
public:
//    typedef sc_bv<DC_OUTPUT_WIDTH> dc_out_t;
//    typedef std::vector<dc_out_word> stub_buffer_type;
//
//    static const unsigned int dc_output_data_width = DC_OUTPUT_WIDTH - 2;
//    static const unsigned int dc_output_data_upper = dc_output_data_width - 1;
//    static const unsigned int dc_output_debug_pos = DC_OUTPUT_WIDTH - 2;
//    static const unsigned int dc_output_valid_pos = DC_OUTPUT_WIDTH - 1;
//
//    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;
//    sc_map_square<sc_in<fe_out_data> > fe_stub_in;
//    sc_out<dc_out_t> dc_out;
//
//    // ----- Local Channel Declarations ----------------------------------------
//    sc_signal<sc_uint<NBITS(NR_DC_WINDOW_CYCLES-1)> > clock_phase;
//    sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES> output_buffer;
//    std::vector<stub_buffer_type> stub_buffer;
//
//    /** Control signal that switches between the two stub tables */
//    sc_signal<unsigned int> stub_buffer_write_sel;
//    sc_signal<unsigned int> stub_buffer_read_sel;
//
//    // ----- Process Declarations ----------------------------------------------
//    void controller();
//    void read_FE_chips();
//    void write_output();
//
//    // ----- Other Method Declarations -----------------------------------------
//
//    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    data_concentrator_mpa(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator_mpa);

//private:
//    void create_output_buffer();
};
