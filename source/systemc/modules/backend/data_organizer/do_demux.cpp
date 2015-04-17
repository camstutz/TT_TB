/*!
 * @file do_demux.cpp
 * @author Christian Amstutz
 * @date April 16, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "do_demux.hpp"

// *****************************************************************************

const unsigned int do_demux::proc_unit_output_nr = 4;

// *****************************************************************************

/*!
 * @class do_input_collector
 *
 * The module is sensitive to ...
 */

do_demux::do_demux(sc_module_name _name) :
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
void do_demux::transfer_stubs()
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
