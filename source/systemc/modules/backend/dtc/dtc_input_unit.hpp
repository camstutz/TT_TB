/*!
 * @file dtc_input_unit.hpp
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

#include "../../../data_formats/gbt_link_format.hpp"
#include "../../../data_formats/CIC_format/CIC_format.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

#include <iostream>

/*!
 * @brief
 */
class dtc_input_unit : public sc_module
{
public:
    typedef gbt_link_format input_t;
    typedef CIC_frame input_frame_t;
    typedef PRBF_0::stub_element_t output_t;

    static const unsigned int fe_collect_cycles;
    const unsigned int fe_id;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<input_t> gbt_input;

    sc_map_linear<sc_fifo_out<output_t> > bx_sorted_stubs;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void process_stubs();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc_input_unit(sc_module_name _name);
    SC_HAS_PROCESS(dtc_input_unit);
};
