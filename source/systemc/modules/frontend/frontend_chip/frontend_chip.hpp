/*!
 * @file frontend_chip.hpp
 * @author Christian Amstutz
 * @date August 22, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/stub/stub.hpp"
#include "frontend_chip_config.hpp"

#include "sc_delay_signal.hpp"
#include "sc_map.hpp"

#include <systemc.h>

#include <vector>
#include <map>
#include <string>

/*!
 * @brief
 */
class frontend_chip: public sc_module
{
public:
    typedef stub input_stub_t;
    typedef stub output_stub_t;

// ----- Configuration ---------------------------------------------------------
    stub_config input_stub_config;
    stub_config output_stub_config;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_fifo_in<input_stub_t> stub_input;
    sc_map_linear<sc_out<bool> > data_valid;
    sc_map_linear<sc_out<output_stub_t> > stub_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<output_stub_t> selected_stubs;
    sc_map_linear<sc_signal<bool> > data_valid_sig;
    sc_map_linear<sc_signal<output_stub_t> > stub_output_sig;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    sc_map_linear<sc_delay_signal<bool> > delay_data_valid;
    sc_map_linear<sc_delay_signal<output_stub_t> > delay_stub_output;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip(const sc_module_name _name, frontend_chip_config configuration);
    SC_HAS_PROCESS(frontend_chip);

private:
    unsigned int max_stubs_per_cycle;
    unsigned int collection_cycles;
    unsigned int total_collected_stubs;

	typedef std::multimap<typename output_stub_t::bend_t, output_stub_t> ordering_buffer_t;

	ordering_buffer_t ordered_stubs;
    std::vector<std::vector<input_stub_t> > collection_buffer;

    void prioritize_hits();
};
