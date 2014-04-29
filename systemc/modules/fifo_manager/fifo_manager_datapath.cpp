/*!
 * @file fifo_manager_datapath.cpp
 * @author Christian Amstutz
 * @date Apr 28, 2014
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
        stub_in(NR_DO_OUT_STUBS, "stub_in"),
        fifo_out(NR_AM_BOARDS, "fifo_out")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_stubs);
        sensitive << clk.pos();
    SC_THREAD(write_fifos);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

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
                for (auto& single_in : stub_in)
                {
                    auto input_value = single_in.read();
                    if (input_value.get_dv())
                    {
                        fm_out_data buffer_value;
                        buffer_value.set_data_valid_flag(true);
                        buffer_value.set_data_stub(input_value.get_data());
                        stub_buffer[AM_lane].push(buffer_value);
                    }
                }
                if (!stub_buffer[AM_lane].empty())
                {
                    fm_out_data time_stamp_data;
                    time_stamp_data.set_data_time_stamp(time_stamp.read());
                    stub_buffer[AM_lane].push(time_stamp_data);
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
            auto read_this_lane = buffer_read_en[AM_lane].read();
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
