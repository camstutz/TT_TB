/*!
 * @file front_end_chip.hpp
 * @author Christian Amstutz
 * @date Feb 21, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <algorithm>
#include <string>
#include <sstream>
#include <array>

#include <systemc.h>

#include "../lib/systemc_helpers/sc_map/sc_map_linear.hpp"

#include "TT_configuration.hpp"
#include "stub.hpp"
#include "fe_out_data.hpp"

/*!
 * @brief
 */
//* todo: If data is written at the clock cycle it will be lost
class front_end_chip : public sc_module
{
public:
    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> en;
    sc_fifo_in<stub> stub_input;
    sc_map_linear<sc_out<fe_out_data> > hit_outputs;

    // ----- Local Channel Declarations ----------------------------------------
    sc_fifo<stub> selected_stubs;

    // ----- Process Declarations ----------------------------------------------
    void prioritize_hits();
    void write_hits();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    /*!
     * Constructor:
     */
    front_end_chip(const sc_module_name _name);
    SC_HAS_PROCESS(front_end_chip);
    void end_of_elaboration();

private:

};
