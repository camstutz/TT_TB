/*!
 * @file dtc_output_unit.hpp
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

#include "../../../systems/tt_tb_logger.hpp"
#include "dtc_buffer_element.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"
#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

#include <iostream>

/*!
 * @brief
 */
class dtc_output_unit : public sc_module
{
public:
    typedef PRBF_0::stub_element_t input_t;
    typedef PRBF_0 output_t;

    static const unsigned int dtc_input_nr;
    static const unsigned int fe_collect_cycles;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<unsigned int> relative_bx;
    sc_in<unsigned int> read_buffer;
    sc_map_cube<sc_fifo_in<dtc_buffer_element> > bx_buffer_inputs;

    sc_out<output_t> tower_out_stream;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void generate_frame();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    dtc_output_unit(sc_module_name _name);
    SC_HAS_PROCESS(dtc_output_unit);

private:
    std::vector<std::vector<std::vector<input_t> > > output_buffer;
};
