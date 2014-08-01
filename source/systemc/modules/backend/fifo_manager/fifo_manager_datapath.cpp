/*!
 * @file fifo_manager_datapath.cpp
 * @author Christian Amstutz
 * @date Aug 1, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "fifo_manager_datapath.hpp"

// *****************************************************************************

/*!
 * @class fifo_manager_datapath
 *
 * The module is sensitive to ...
 */

fifo_manager_datapath::fifo_manager_datapath(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        buffer_write_en(NR_AM_BOARDS, "buffer_write_en"),
        buffer_read_en(NR_AM_BOARDS, "buffer_read_en"),
        time_stamp("time_stamp"),
        dv_in(NR_DO_OUT_STUBS, "dv_in"),
        stub_in(NR_DO_OUT_STUBS, "stub_in"),
        neighbour_dv_in(NR_NEIGHBOURING_TOWERS, "neighbour_dv_in"),
        neighbour_stub_in(NR_NEIGHBOURING_TOWERS, "neighbour_stub_in"),
        neighbour_dv_out(NR_NEIGHBOURING_TOWERS, "neighbour_dv_out"),
        neighbour_stub_out(NR_NEIGHBOURING_TOWERS, "neighbour_stub_out"),
        dv_out(NR_AM_BOARDS, "dv_out"),
        fifo_out(NR_AM_BOARDS, "fifo_out")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_stubs);
        sensitive << clk.pos();
    SC_THREAD(write_fifos);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    stub_buffer.resize(NR_AM_BOARDS);

    return;
}

// *****************************************************************************
void fifo_manager_datapath::read_stubs()
{
    while (1)
    {
        wait();

        for (unsigned int AM_lane = 0; AM_lane < NR_AM_BOARDS; ++AM_lane)
        {
            if (buffer_write_en[AM_lane].read())
            {
                // Iterate over all inputs of the layer
                sc_map_linear<sc_in<data_organizer_one_layer::do_stub_t> >::iterator input_it = stub_in.begin();
                sc_map_linear<sc_in<bool> >::iterator dv_it = dv_in.begin();
                for (; input_it != stub_in.end(); ++input_it)
                {
                    if (dv_it->read() == true)
                    {
                        stub_buffer[AM_lane].push(fm_out_data(input_it->read()));
                    }

                    ++dv_it;
                }
                if (!stub_buffer[AM_lane].empty())
                {
                    stub_buffer[AM_lane].push(fm_out_data(time_stamp.read()));
                }
            }
        }
    }

}

// *****************************************************************************
void fifo_manager_datapath::write_fifos()
{
    while(1)
    {
        wait();

        for (unsigned int AM_lane = 0; AM_lane < NR_AM_BOARDS; ++AM_lane)
        {
            bool read_this_lane = buffer_read_en[AM_lane].read();
            if (read_this_lane & !stub_buffer[AM_lane].empty())
            {
                fm_out_data output_data = stub_buffer[AM_lane].front();
                stub_buffer[AM_lane].pop();
                fifo_out[AM_lane].write(output_data);
            }
            else
            {
                fifo_out[AM_lane].write(fm_out_data());
            }
        }
    }

}
