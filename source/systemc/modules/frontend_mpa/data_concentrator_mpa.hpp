/*!
 * @file data_concentrator_mpa.hpp
 * @author Christian Amstutz
 * @date July 3, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

// todo: create data_concentrator base and inherit from it

#pragma once

#include <vector>
#include <utility>

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../libraries/systemc_helpers/nbits.hpp"

#include "../../systems/TT_configuration.hpp"
#include "../../data_formats/stub_bxpsb.hpp"
#include "../../data_formats/stub_vbxpfsb.hpp"
#include "../../data_formats/dc_out_word.hpp"

/*!
 * @brief
 */
class data_concentrator_mpa : public sc_module
{
public:
    typedef stub_bxpsb<FE_MPA_STUB_BX_BITS,
                       FE_MPA_STUB_PIXEL_BITS,
                       FE_MPA_STUB_STRIP_BITS,
                       FE_MPA_STUB_BEND_BITS,
                       FE_MPA_STUB_BX_BITS+FE_MPA_STUB_PIXEL_BITS+
                       FE_CBC_STUB_STRIP_BITS+FE_CBC_STUB_BEND_BITS> in_stub_t;
    typedef stub_vbxpfsb<DC_STUB_BX_BITS,
                         FE_MPA_STUB_PIXEL_BITS,
                         DC_STUB_FE_BITS,
                         FE_MPA_STUB_STRIP_BITS,
                         FE_MPA_STUB_BEND_BITS,
                         DC_STUB_BX_BITS+FE_MPA_STUB_PIXEL_BITS+DC_STUB_FE_BITS+
                         FE_MPA_STUB_STRIP_BITS+FE_MPA_STUB_BEND_BITS>
                         mpa_out_stub_t;
    typedef dc_out_word<DC_OUT_HEADER_BITS,
                        DC_OUTPUT_WIDTH-DC_OUT_HEADER_BITS,
                        DC_OUTPUT_WIDTH> dc_out_t;
    typedef std::vector<mpa_out_stub_t> stub_buffer_type;
    typedef unsigned int clock_phase_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;
    sc_map_square<sc_in<bool> > data_valid;
    sc_map_square<sc_in<in_stub_t> > fe_stub_in;
    sc_out<dc_out_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<clock_phase_t> clock_phase;
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
    data_concentrator_mpa(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator_mpa);

private:
    void create_output_buffer();
    mpa_out_stub_t::bx_t calculate_bx(clock_phase_t clock_phase,
            in_stub_t::bx_t stub_bx);
};
