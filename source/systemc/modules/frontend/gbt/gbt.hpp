/*!
 * @file gbt.hpp
 * @author Christian Amstutz
 * @date August 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "sc_map.hpp"
#include "../../../data_formats/CIC_frame/CIC_frame.hpp"
#include "../../../data_formats/gbt_link_format/gbt_link_format.hpp"
#include "../../../systems/tt_tb_logger.hpp"

#include "gbt_config.hpp"

#include <systemc.h>

#include <vector>
#include <utility>

// *****************************************************************************
/*!
 * @brief
 */
class gbt : public sc_module
{
private:
    const unsigned int input_link_count;

public:
	// ----- Configuration -----------------------------------------------------
	typedef CIC_frame input_t;
    typedef gbt_link_format output_t;

    // ----- Port Declarations -------------------------------------------------
    sc_map_linear<sc_in<input_t> > cic_in;

    sc_out<output_t> optical_link;

    // ----- Local Channel Declarations ----------------------------------------

    // ----- Process Declarations ----------------------------------------------
    void combine_inputs();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    gbt(sc_module_name _name, gbt_config configuration);
    SC_HAS_PROCESS(gbt);
};
