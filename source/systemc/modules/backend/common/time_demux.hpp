/*!
 * @file time_demux.hpp
 * @author Christian Amstutz
 * @date April 23, 2015
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
template <typename FRAME_T, unsigned int LAYER_NR, unsigned int PROC_OUT_NR, int TIMER_START>
class time_demux : public sc_module
{
public:
    typedef FRAME_T frame_t;
    typedef typename frame_t::stub_element_t input_t;
    typedef frame_t output_t;
    typedef typename frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef bunch_crossing_t request_t;

    static const unsigned int layer_nr;
    static const unsigned int proc_unit_output_nr;
    static const int timer_start;

// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;

    sc_out<request_t> bunch_crossing_request;
    sc_map_linear<sc_fifo_in<input_t> > stub_input;

    sc_map_square<sc_out<output_t> > proc_unit_outputs;

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
    time_demux(sc_module_name _name, unsigned int bx_divider, unsigned int bx_offset);
    SC_HAS_PROCESS(time_demux);

private:
    unsigned int bx_divider;
    unsigned int bx_offset;
};

// *****************************************************************************

// *****************************************************************************

template <typename FRAME_T, unsigned int LAYER_NR, unsigned int PROC_OUT_NR, int TIMER_START>
const unsigned int time_demux<FRAME_T, LAYER_NR, PROC_OUT_NR, TIMER_START>::layer_nr = LAYER_NR;

template <typename FRAME_T, unsigned int LAYER_NR, unsigned int PROC_OUT_NR, int TIMER_START>
const unsigned int time_demux<FRAME_T, LAYER_NR, PROC_OUT_NR, TIMER_START>::proc_unit_output_nr = PROC_OUT_NR;

template <typename FRAME_T, unsigned int LAYER_NR, unsigned int PROC_OUT_NR, int TIMER_START>
const int time_demux<FRAME_T, LAYER_NR, PROC_OUT_NR, TIMER_START>::timer_start = TIMER_START;

// *****************************************************************************
template <typename FRAME_T, unsigned int LAYER_NR, unsigned int PROC_OUT_NR, int TIMER_START>
time_demux<FRAME_T, LAYER_NR, PROC_OUT_NR, TIMER_START>::time_demux(
        sc_module_name _name, unsigned int bx_divider, unsigned int bx_offset) :
        sc_module(_name),
        clk("clk"),
        bunch_crossing_request("bunch_crossing_request"),
        stub_input(layer_nr, "stub_input"),
        proc_unit_outputs(proc_unit_output_nr, layer_nr, "remote_proc_unit_output"),
        bx_counter("bx_counter"),
        bx_divider(bx_divider),
        bx_offset(bx_offset)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(transfer_stubs);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    bx_counter.write(timer_start);

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename FRAME_T, unsigned int LAYER_NR, unsigned int PROC_OUT_NR, int TIMER_START>
void time_demux<FRAME_T, LAYER_NR, PROC_OUT_NR, TIMER_START>::transfer_stubs()
{
    while (1)
    {
        wait();

        bunch_crossing_request.write(bx_counter.read());

        if ((bx_counter.read() % bx_divider) == bx_offset)
        {
            for(unsigned int layer_id = 0; layer_id < layer_nr; ++layer_id)
            {
                frame_t output_frame(bx_counter.read()-1);
                while (stub_input[layer_id].num_available() > 0)
                {
                    output_frame.add_stub(stub_input[layer_id].read());
                }
                proc_unit_outputs.at(((bx_counter.read() - bx_offset) / bx_divider)%proc_unit_output_nr, layer_id).write(output_frame);

                if (output_frame.stub_count() > 0)
                {
                    SYSTEMC_LOG << "Frame " << output_frame.get_bunch_crossing()
                            << " with " << output_frame.stub_count() << " stubs sent to "
                            << "(out=" << (((bx_counter.read() - bx_offset) / bx_divider)%proc_unit_output_nr)
                            << ", layer=" << layer_id << ").";
                }
            }
        }

        bx_counter.write(bx_counter.read() + 1);
    }

}
