/*!
 * @file fifo_ctrl.cpp
 * @author Christian Amstutz
 * @date February 17, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "fifo_ctrl.hpp"

// *****************************************************************************

/*!
 * @class hit_ctrl_single_line
 *
 * The module is sensitive to ...
 */

fifo_ctrl::fifo_ctrl(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        event_start("event_start"),
        transmission_start("transmission_start"),
        event_active("event_active"),
        stub_input("stub_input"),
        fifo_read_en("fifo_read_en"),
        stub_output("stub_output"),
        event_start_sig("event_start_sig"),
        is_timestamp_sig("is_timestamp_sig"),
        FSM("FSM")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_stub);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------
    FSM.clk.bind(clk);
    FSM.event_start.bind(event_start);
    FSM.is_timestamp.bind(is_timestamp_sig);
    FSM.event_active.bind(event_active);
    FSM.fifo_read_en.bind(fifo_read_en);

    return;
}

// *****************************************************************************
void fifo_ctrl::process_stub()
{
    while (1)
    {
        wait();

        if (transmission_start.read() == true)
        {
            is_timestamp_sig.write(false);
            stub_output.write(track_finder::hit_stream::START_WORD);
        }
        else if (event_active.read())
        {
            fm_out_data input_stub = stub_input.read();
            if (input_stub.is_timestamp())
            {
                is_timestamp_sig.write(true);
                stub_output.write(track_finder::hit_stream::IDLE);
            }
            else
            {
                is_timestamp_sig.write(false);
                stub_output.write(input_stub.get_data_stub().get_bitvector().to_uint());
            }
        }
    }

}
