/*!
 * @file data_concentrator.hpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <utility>

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"
#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../systems/tt_tb_logger.hpp"

#include "../../systems/TT_configuration.hpp"
#include "data_concentrator_config.hpp"

#include "../../data_formats/stub/stub.hpp"
#include "../../data_formats/CIC_frame/CIC_frame.hpp"

/*!
 * @brief
 */
class data_concentrator : public sc_module
{
private:
    const unsigned int nr_fe_chips;
    const unsigned int max_in_stubs_per_cycle;
    const unsigned int collection_cycles;
    const unsigned int max_output_stubs;
    const unsigned int output_window_cycles;

public:
	// ----- Configuration -----------------------------------------------------
	typedef stub fe_stub_t;
	typedef CIC_frame output_t;
	typedef stub output_stub_t;

	// -------------------------------------------------------------------------

    typedef std::vector<output_stub_t> stub_buffer_type;
    typedef output_t::header_t::bunch_crossing_t bunch_crossing_t;
    typedef unsigned int clock_phase_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_square<sc_in<bool> > data_valid;
    sc_map_square<sc_in<fe_stub_t> > fe_stub_in;
    sc_out<output_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bunch_crossing_t> LHC_bunch_crossing;
    sc_signal<clock_phase_t> clock_phase;
    std::vector<stub_buffer_type> stub_buffer;
    sc_signal<output_t> dc_out_sig;

    /** Control signal that switches between the two stub tables */
    sc_signal<bool> stub_buffer_write_sel;
    sc_signal<bool> stub_buffer_read_sel;

    // ----- Process Declarations ----------------------------------------------
    void controller();
    void read_FE_chips();
    void write_output();

    // ----- Other Method Declarations -----------------------------------------
    output_t create_output_buffer();

    // ----- Module Instantiations ---------------------------------------------
    sc_delay_signal<output_t, DC_output_delay> delay_output;

    // ----- Constructor -------------------------------------------------------
    data_concentrator(sc_module_name _name, data_concentrator_config configuration);
    SC_HAS_PROCESS(data_concentrator);

    typename output_stub_t::bx_t calculate_bx(clock_phase_t clock_phase, typename fe_stub_t::bx_t stub_bx);

private:
    stub_config output_stub_config;
};
