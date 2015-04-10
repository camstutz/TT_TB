/*!
 * @file gbt.hpp
 * @author Christian Amstutz
 * @date April 10, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../data_formats/CIC_format/CIC_format.hpp"
#include "../../data_formats/gbt_link_format.hpp"

#include <systemc.h>

#include <vector>
#include <utility>

/*!
 * @brief
 */
class gbt : public sc_module
{
public:
	// ----- Configuration -----------------------------------------------------
	typedef CIC_frame input_t;
    typedef gbt_link_format output_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<input_t> > cic_in;

    sc_out<output_t> optical_link;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------
    void combine_inputs();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    gbt(sc_module_name _name);
    SC_HAS_PROCESS(gbt);
};
