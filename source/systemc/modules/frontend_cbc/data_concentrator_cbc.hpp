/*!
 * @file data_concentrator_cbc.hpp
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
#include "../../data_formats/stub_sb.hpp"
#include "../../data_formats/stub_vbxfsb.hpp"
#include "../../data_formats/dc_out_word.hpp"

/*!
 * @brief
 */
class data_concentrator_cbc : public sc_module
{
public:
    typedef stub_sb<FE_CBC_STUB_STRIP_BITS,
                    FE_CBC_STUB_BEND_BITS,
                    FE_CBC_STUB_STRIP_BITS+FE_CBC_STUB_BEND_BITS> in_stub_t;
    typedef stub_vbxfsb<DC_STUB_BX_BITS,
                        DC_STUB_FE_BITS,
                        FE_CBC_STUB_STRIP_BITS,
                        FE_CBC_STUB_BEND_BITS,
                        DC_STUB_BX_BITS+DC_STUB_FE_BITS+FE_CBC_STUB_STRIP_BITS
                        +FE_CBC_STUB_BEND_BITS> cbc_out_stub_t;
    typedef dc_out_word<DC_OUT_HEADER_BITS,
                        DC_OUTPUT_WIDTH-DC_OUT_HEADER_BITS,
                        DC_OUTPUT_WIDTH> dc_out_t;
    typedef std::vector<cbc_out_stub_t> stub_buffer_type;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_map_square<sc_in<bool> > data_valid;
    sc_map_square<sc_in<in_stub_t> > fe_stub_in;
    sc_out<dc_out_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<sc_uint<NBITS(NR_DC_WINDOW_CYCLES-1)> > clock_phase;
    sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES> output_buffer;
    std::vector<stub_buffer_type> stub_buffer;

    /** Control signal that switches between the two stub tables */
    sc_signal<unsigned int> stub_buffer_write_sel;
    sc_signal<unsigned int> stub_buffer_read_sel;

    // ----- Process Declarations ----------------------------------------------
    void controller();
    void read_FE_chips();
    void write_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    data_concentrator_cbc(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator_cbc);

private:
    void create_output_buffer();
};
