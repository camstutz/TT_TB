/*!
 * @file processor_organizer.hpp
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

#include "../common/input_collector.hpp"
#include "../common/bx_stub_buffer.hpp"
#include "../common/time_demux.hpp"
#include "po_layer_splitter.hpp"
#include "../../../data_formats/prbf/PRBF.hpp"
//#include "../../../systems/TT_configuration.hpp"
#include "processor_organizer_config.hpp"


#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>
#include "../common/time_demux.hpp"

/*!
 * @brief
 */
class processor_organizer : public sc_module
{
public:
    //typedef input_collector<PRBF_1, PRBF_2, NR_PRB_PER_TRIGGER_TOWER> po_input_collector;
    typedef input_collector<PRBF_1, PRBF_2> po_input_collector;
    typedef bx_stub_buffer<PRBF_2> po_stub_buffer;
    //typedef time_demux<PRBF_2, NR_DETECTOR_LAYERS, NR_AM_BOARDS, PO_COUNTER_CORRECTION> po_demux;
    typedef time_demux<PRBF_2> po_demux;

    typedef PRBF_1 do_input_t;
    typedef PRBF_2 processor_output_t;

    const unsigned int do_input_nr;
    const unsigned int layer_nr;
    const unsigned int processor_output_nr;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_map_linear<sc_in<do_input_t> > do_inputs;

    sc_map_square<sc_out<processor_output_t> > processor_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<po_input_collector::output_t> stub_buffer_input_fifo;
    sc_buffer<po_stub_buffer::bunch_crossing_t> bunch_request_sig;
    sc_fifo<po_stub_buffer::output_t> stub_buffer_output_fifo;
    sc_map_linear<sc_fifo<po_stub_buffer::output_t> > splitted_stubs_fifos;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------
    po_input_collector in_collector;
    po_stub_buffer stub_buffer;
    po_layer_splitter layer_splitter;
    po_demux demultiplexer;

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    processor_organizer(sc_module_name _name, processor_organizer_config configuration);
};
