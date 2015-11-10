/*!
 * @file frontend_chip.hpp
 * @author Christian Amstutz
 * @date November 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/stub/stub.hpp"
#include "buffer_stub.hpp"
#include "frontend_chip_config.hpp"

#include "sc_delay_signal.hpp"
#include "sc_map.hpp"

#include <systemc.h>

#include <vector>
#include <map>
#include <set>
#include <string>

/*!
 * @brief
 */
class frontend_chip: public sc_module
{
public:
    typedef stub input_stub_t;
    typedef stub output_stub_t;
    typedef buffer_stub sorted_buffer_stub_t;

// ----- Configuration ---------------------------------------------------------
    stub_config input_stub_config;
    stub_config output_stub_config;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_fifo_in<input_stub_t> stub_input;
    sc_map_linear<sc_out<bool> > data_valid;
    sc_map_linear<sc_out<output_stub_t> > stub_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<unsigned int> clock_cycle;
    sc_signal<unsigned int> wbuf_selector;
    sc_signal<unsigned int> rbuf_selector;

// ----- Process Declarations --------------------------------------------------
    void controller();
    void read_input();
    void write_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

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

    std::vector<std::set<sorted_buffer_stub_t> > sorted_buffers;
};
