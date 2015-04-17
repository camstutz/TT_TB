/*!
 * @file time_demux.hpp
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

#include "../../../systems/TT_configuration.hpp"

#include "../../../libraries/systemc_helpers/sc_map/sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
template <typename FRAME_T, unsigned int PROC_OUT_NR>
class time_demux : public sc_module
{
public:
    typedef FRAME_T frame_t;
    typedef typename frame_t::stub_element_t input_t;
    typedef frame_t output_t;
    typedef typename frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
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
    time_demux(sc_module_name _name);
    SC_HAS_PROCESS(time_demux);
};

// *****************************************************************************

// *****************************************************************************

template <typename FRAME_T, unsigned int PROC_OUT_NR>
const unsigned int time_demux<FRAME_T, PROC_OUT_NR>::proc_unit_output_nr = PROC_OUT_NR;

// *****************************************************************************
template <typename FRAME_T, unsigned int PROC_OUT_NR>
time_demux<FRAME_T, PROC_OUT_NR>::time_demux(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        bunch_crossing_request("bunch_crossing_request"),
        stub_input("stub_input"),
        proc_unit_outputs(proc_unit_output_nr, "remote_proc_unit_output"),
        bx_counter("bx_counter")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(transfer_stubs);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    bx_counter.write(-20);

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename FRAME_T, unsigned int PROC_OUT_NR>
void time_demux<FRAME_T, PROC_OUT_NR>::transfer_stubs()
{
    while (1)
    {
        wait();

        bunch_crossing_request.write(bx_counter.read());

        frame_t output_frame(bx_counter.read()-1);
        while (stub_input.num_available() > 0)
        {
            output_frame.add_stub(stub_input.read());
        }
        proc_unit_outputs[bx_counter.read()%proc_unit_output_nr].write(output_frame);

        bx_counter.write(bx_counter.read() + 1);
    }

}

