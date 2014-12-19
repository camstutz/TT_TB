/*!
 * @file frontend_chip_mpa.hpp
 * @author Christian Amstutz
 * @date December 19, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <map>

#include <systemc.h>
#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
class frontend_chip_mpa : public sc_module
{
public:
    typedef fe_mpa_stub_t stub_t;

    static const unsigned int max_hits_per_cycle;
    static const unsigned int collection_cycles;
    static const unsigned int total_hits;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_fifo_in<stub_t> stub_input;
    sc_map_linear<sc_out<bool> > data_valid;
    sc_map_linear<sc_out<stub_t> > stub_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<fe_mpa_stub_t> selected_stubs;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip_mpa(const sc_module_name _name);
    SC_HAS_PROCESS(frontend_chip_mpa);

private:
    std::vector<std::vector<stub_t> > collection_buffer;

    void prioritize_hits();
};
