/*!
 * @file do_input_collector.hpp
 * @author Christian Amstutz
 * @date April 16, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "do_stub_buffer.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

#include <utility>
#include <map>
#include <iostream>

/*!
 * @brief
 */
class do_input_collector : public sc_module
{
public:
    typedef PRBF_0 input_frame_t;
    typedef input_frame_t input_t;
    typedef PRBF_1 output_frame_t;
    typedef do_stub_buffer::input_pair output_t;
    typedef input_frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;

    static const unsigned int dtc_input_nr;

// ----- Port Declarations -----------------------------------------------------
    sc_map_linear<sc_in<input_t> > dtc_inputs;

    sc_fifo_out<output_t> stub_output;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void process_incoming_frame();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    do_input_collector(sc_module_name _name);
    SC_HAS_PROCESS(do_input_collector);
};
