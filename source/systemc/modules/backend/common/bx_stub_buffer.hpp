/*!
 * @file bx_stub_buffer.hpp
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
template <typename FRAME_T>
class bx_stub_buffer : public sc_module
{
public:
    typedef FRAME_T frame_t;
    typedef typename frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef bunch_crossing_t index_t;
    typedef typename frame_t::stub_element_t element_t;
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
    bx_stub_buffer(sc_module_name _name);
    SC_HAS_PROCESS(bx_stub_buffer);
};

// *****************************************************************************

// *****************************************************************************
template <typename FRAME_T>
bx_stub_buffer<FRAME_T>::bx_stub_buffer(sc_module_name _name) :
        sc_module(_name),
        stub_input("stub_input"),
        bunch_crossing_select("bunch_crossing_select"),
        stub_output("stub_output")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frame);
        sensitive << stub_input.data_written();
    SC_THREAD(read_frame);
        sensitive << bunch_crossing_select;

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename FRAME_T>
void bx_stub_buffer<FRAME_T>::bx_stub_buffer::write_frame()
{
    while (1)
    {
        wait();

        while (stub_input.num_available() > 0)
        {
            input_pair_t input_stub = stub_input.read();
            bx_buffer[input_stub.first].push_back(input_stub.second);
        }
    }

}

// *****************************************************************************
template <typename FRAME_T>
void bx_stub_buffer<FRAME_T>::bx_stub_buffer::read_frame()
{
    while (1)
    {
        wait();

        bunch_crossing_t bx = bunch_crossing_select.read();

        // Test if frame is available for current bunch crossing
        if (bx_buffer.find(bx) != bx_buffer.end())
        {
            std::vector<element_t> stub_vector = bx_buffer[bx];
            typename std::vector<element_t>::iterator stub_it = stub_vector.begin();
            for (; stub_it != stub_vector.end(); ++stub_it)
            {
                if (!stub_output.nb_write(*stub_it))
                {
                    std::cerr << sc_time_stamp() << ": FIFO overflow @ "
                              << name() << ".stub_output" << std::endl;
                }
            }

            // delete bunch crossing entry
            bx_buffer.erase(bx);
        }
    }

}

