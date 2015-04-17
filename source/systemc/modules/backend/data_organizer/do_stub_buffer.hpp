/*!
 * @file do_stub_buffer.hpp
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
#include "../../../data_formats/sc_pair/sc_pair.hpp"

#include "../../../systems/TT_configuration.hpp"

#include "../../../data_formats/sc_pair/sc_pair.hpp"

#include <systemc.h>

#include <map>
#include <iostream>

/*!
 * @brief
 */
class do_stub_buffer : public sc_module
{
public:
    typedef PRBF_1 frame_t;
    typedef frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef bunch_crossing_t index_t;
    typedef frame_t::stub_element_t element_t;
    typedef sc_pair<index_t, element_t> input_pair_t;
    typedef element_t output_t;
    typedef std::map<index_t, std::vector<element_t> > buffer_t;

// ----- Port Declarations -----------------------------------------------------
    sc_fifo_in<input_pair_t> stub_input;
    sc_in<bunch_crossing_t> bunch_crossing_select;

    sc_fifo_out<output_t> stub_output;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------
    buffer_t bx_buffer;

// ----- Process Declarations --------------------------------------------------
    void write_frame();
    void read_frame();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    do_stub_buffer(sc_module_name _name);
    SC_HAS_PROCESS(do_stub_buffer);
};
