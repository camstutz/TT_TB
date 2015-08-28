/*!
 * @file data_organizer.hpp
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

#include "../common/input_collector.hpp"
#include "../common/bx_stub_buffer.hpp"
#include "../common/time_demux.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"
#include "../../../modules/backend/data_organizer/data_organizer_config.hpp"
#include "../../../systems/TT_configuration.hpp"

#include "sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
class data_organizer : public sc_module
{
public:
    typedef input_collector<PRBF_0, PRBF_1> do_input_collector;
    typedef bx_stub_buffer<PRBF_1> do_stub_buffer;
    typedef time_demux<PRBF_1> do_demux;

    typedef PRBF_0 dtc_input_t;
    typedef PRBF_1 proc_unit_output_t;

    const data_organizer_config configuration;
    const unsigned int dtc_input_nr;
    const unsigned int proc_unit_nr;

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
    do_input_collector in_collector;
    do_stub_buffer stub_buffer;
    do_demux demultiplexer;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    data_organizer(sc_module_name _name, data_organizer_config configuration);
};
