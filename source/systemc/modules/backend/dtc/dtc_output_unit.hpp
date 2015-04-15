/*!
 * @file dtc_output_unit.hpp
 * @author Christian Amstutz
 * @date April 14, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

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

    static const unsigned int fe_collect_cycles;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<unsigned int> bunch_crossing;
    sc_in<unsigned int> read_buffer;
    sc_in<unsigned int> write_buffer;
    sc_map_linear<sc_fifo_in<input_t> > bx_sorted_stubs;

    sc_out<output_t> tower_out_stream;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void read_input();
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
