/*!
 * @file time_demux.hpp
 * @author Christian Amstutz
 * @date October 13, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/prbf/PRBF.hpp"

#include "time_demux_config.hpp"
#include "../../../systems/TT_configuration.hpp"
#include "../../../systems/tt_tb_logger.hpp"

#include "sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
template <typename FRAME_T>
class time_demux : public sc_module
{
public:
    typedef FRAME_T frame_t;
    typedef typename frame_t::stub_element_t input_t;
    typedef frame_t output_t;
    typedef typename frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef bunch_crossing_t request_t;

    const unsigned int layer_nr;
    const unsigned int proc_unit_output_nr;
    const int timer_start;
    const unsigned int bx_divider;
    const unsigned int bx_offset;

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
    time_demux(sc_module_name _name, time_demux_config configuration);
    SC_HAS_PROCESS(time_demux);
};

// *****************************************************************************

// *****************************************************************************
template <typename FRAME_T>
time_demux<FRAME_T>::time_demux(sc_module_name _name,
        time_demux_config configuration) :
        sc_module(_name),
        layer_nr(configuration.layer_nr),
        proc_unit_output_nr(configuration.proc_unit_nr),
        timer_start(configuration.timer_start),
        bx_divider(configuration.bx_divider),
        bx_offset(configuration.bx_offset),
        clk("clk"),
        bunch_crossing_request("bunch_crossing_request"),
        stub_input(layer_nr, "stub_input"),
        proc_unit_outputs(proc_unit_output_nr, layer_nr, "remote_proc_unit_output"),
        bx_counter("bx_counter")
{
    // ----- Process registration ----------------------------------------------
    SC_METHOD(transfer_stubs);
        sensitive << clk.pos();
        dont_initialize();

    // ----- Module channel/variable initialization ----------------------------
    bx_counter.write(timer_start);

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename FRAME_T>
void time_demux<FRAME_T>::transfer_stubs()
{
    bunch_crossing_request.write(bx_counter.read());

    if ((bx_counter.read() % bx_divider) == bx_offset)
    {
        for (unsigned int layer_id = 0; layer_id < layer_nr; ++layer_id)
        {
            frame_t output_frame(bx_counter.read()-1);
            while (stub_input[layer_id].num_available() > 0)
            {
                output_frame.add_stub(stub_input[layer_id].read());
            }
            proc_unit_outputs.at(((bx_counter.read() - bx_offset) / bx_divider)%proc_unit_output_nr, layer_id).write(output_frame);

           // if (output_frame.stub_count() > 0)
           // {
                //SYSTEMC_LOG << "Frame " << output_frame.get_bunch_crossing()
                //        << " with " << output_frame.stub_count() << " stubs sent to "
                //        << "(out=" << (((bx_counter.read() - bx_offset) / bx_divider)%proc_unit_output_nr)
                //        << ", layer=" << layer_id << ").";
            //}
        }
    }

    bx_counter.write(bx_counter.read() + 1);

    return;
}
