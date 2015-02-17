/*!
 * @file frontend_chip_cbc.hpp
 * @author Christian Amstutz
 * @date February 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"

#include "../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
class frontend_chip_cbc : public sc_module
{
public:
    typedef fe_cbc_stub_t stub_t;

    static const unsigned int max_input_hits;
    static const unsigned int max_hits_per_cycle;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_fifo_in<stub_t> stub_input;
    sc_map_linear<sc_out<bool> > data_valid;
    sc_map_linear<sc_out<stub_t> > stub_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<stub_t> selected_stubs;

// ----- Process Declarations --------------------------------------------------
    void prioritize_hits();
    void write_hits();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    frontend_chip_cbc(const sc_module_name _name);
    SC_HAS_PROCESS(frontend_chip_cbc);

private:

};
