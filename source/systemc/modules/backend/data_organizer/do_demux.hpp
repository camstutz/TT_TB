/*!
 * @file do_demux.hpp
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

#include "../../../data_formats/prbf/PRBF.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
class do_demux : public sc_module
{
public:
    typedef PRBF_1 frame_t;
    typedef frame_t::stub_element_t input_t;
    typedef frame_t output_t;
    typedef frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef bunch_crossing_t request_t;

    static const unsigned int proc_unit_output_nr;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;

    sc_out<request_t> bunch_crossing_request;
    sc_fifo_in<input_t> stub_input;

    sc_map_linear<sc_out<output_t> > proc_unit_outputs;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<bunch_crossing_t> bx_counter;

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void transfer_stubs();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    do_demux(sc_module_name _name);
    SC_HAS_PROCESS(do_demux);
};
