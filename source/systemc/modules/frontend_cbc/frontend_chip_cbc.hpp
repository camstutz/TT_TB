/*!
 * @file frontend_chip_cbc.hpp
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

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include "../../systems/TT_configuration.hpp"
#include "../../data_formats/fe_out_data.hpp"

/*!
 * @brief
 */
class frontend_chip_cbc : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> en;
    sc_fifo_in<fe_out_data::fe_stub_t> stub_input;
    sc_map_linear<sc_out<fe_out_data> > hit_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<fe_out_data::fe_stub_t> selected_stubs;

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
