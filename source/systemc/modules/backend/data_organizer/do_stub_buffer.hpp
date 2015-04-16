/*!
 * @file do_stub_buffer.hpp
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

#include <utility>
#include <map>
#include <iostream>

/*!
 * @brief
 */
class do_stub_buffer : public sc_module
{
public:
    typedef PRBF_0::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef bunch_crossing_t index_t;
    typedef PRBF_0::stub_element_t element_t;
    typedef element_t output_t;
    typedef std::map<index_t, std::vector<element_t> > buffer_t;

    class input_pair : public std::pair<index_t, element_t>
    {
    public:
        input_pair();
        input_pair(index_t index, element_t element);
        friend std::ostream& operator<< (std::ostream& stream, const input_pair& pair);
        //friend void sc_trace(sc_trace_file* tf, const input_pair& v, const std::string& name);
    };

// ----- Port Declarations -----------------------------------------------------
    sc_fifo_in<input_pair> stub_input;
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
