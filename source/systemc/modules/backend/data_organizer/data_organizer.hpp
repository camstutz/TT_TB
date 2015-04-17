/*!
 * @file data_organizer.hpp
 * @author Christian Amstutz
 * @date April 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/prbf/PRBF.hpp"
#include "do_input_collector.hpp"
#include "do_stub_buffer.hpp"
#include "do_demux.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
class data_organizer : public sc_module
{
public:
    typedef PRBF_0 dtc_input_t;
    typedef PRBF_1 proc_unit_output_t;

    static const unsigned int dtc_input_nr;
    static const unsigned int proc_unit_nr;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<dtc_input_t> > dtc_inputs;

    sc_map_linear<sc_out<proc_unit_output_t> > proc_unit_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<do_input_collector::output_t> stub_buffer_input_fifo;
    sc_buffer<do_stub_buffer::bunch_crossing_t> bunch_request_sig;
    sc_fifo<do_stub_buffer::output_t> stub_buffer_output_fifo;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    do_input_collector input_collector;
    do_stub_buffer stub_buffer;
    do_demux demultiplexer;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer(sc_module_name _name);
};
