/*!
 * @file dtc_input_unit.hpp
 * @author Christian Amstutz
 * @date April 27, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "dtc_buffer_element.hpp"

#include "../../../data_formats/gbt_link_format.hpp"
#include "../../../data_formats/CIC_format/CIC_format.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"
#include "../../../systems/tt_tb_logger.hpp"
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
    typedef dtc_buffer_element::second_type output_element_t;

    static const unsigned int fe_collect_cycles;
    const unsigned int fe_id;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<input_t> gbt_input;
    sc_in<unsigned int> write_buffer_select;

    sc_map_square<sc_fifo_out<dtc_buffer_element> > bx_buffer_out;

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
