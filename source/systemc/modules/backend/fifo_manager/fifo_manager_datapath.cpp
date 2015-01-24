/*!
 * @file fifo_manager_datapath.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
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
        neighbour_dv_in.make_sensitive(sensitive);
    SC_THREAD(write_fifos);
        sensitive << clk.pos();
    SC_THREAD(write_neighbours);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    stub_buffer.resize(NR_AM_BOARDS);
    neighbour_buffer.resize(NR_NEIGHBOURING_TOWERS);

    return;
}

// *****************************************************************************
void fifo_manager_datapath::read_stubs()
{
    while (1)
    {
        wait();

    	neighbour_dv_out.write_all(false);
    	neighbour_stub_out.write_all(0);

        for (unsigned int AM_lane = 0; AM_lane < NR_AM_BOARDS; ++AM_lane)
        {
            if (buffer_write_en[AM_lane].read())
            {
                // Iterate over all inputs of the layer
                sc_map_linear<sc_in<input_stub_t> >::iterator input_it = stub_in.begin();
                sc_map_linear<sc_in<bool> >::iterator dv_it = dv_in.begin();
                for (; input_it != stub_in.end(); ++input_it)
                {
                    if (dv_it->read() == true)
                    {
                        input_stub_t input_stub = input_it->read();
                        stub_buffer[AM_lane].push(output_t(input_stub));

                        // Check to which neighbours a stub should be
                        // transmitted too.
                        neighbour_vector neighbours = neighbour_selector(input_stub);
                        if (!neighbours.empty())
                        {
                            neighbour_vector::iterator neighbour_it = neighbours.begin();
                            for (; neighbour_it != neighbours.end(); ++neighbour_it)
                            {
                                //neighbour_buffer[*neighbour_it].push(input_stub);
                            	neighbour_dv_out[*neighbour_it].write(true);
                            	neighbour_stub_out[*neighbour_it].write(input_stub);
                            }
                        }
                    }

                    ++dv_it;
                }

                sc_map_linear<sc_in<input_stub_t> >::iterator neighbour_input_it = neighbour_stub_in.begin();
                sc_map_linear<sc_in<bool> >::iterator neighbour_dv_it = neighbour_dv_in.begin();
                for (; neighbour_input_it != neighbour_stub_in.end(); ++neighbour_input_it)
                {
                    if (neighbour_dv_it->read() == true)
                    {
                        input_stub_t input_stub = neighbour_input_it->read();
                        stub_buffer[AM_lane].push(output_t(input_stub));
                    }

                    ++neighbour_dv_it;
                }

                // add time stamp to buffer if there are stubs in the buffer
                if (!stub_buffer[AM_lane].empty())
                {
                    stub_buffer[AM_lane].push(output_t(time_stamp.read()));
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

        dv_out.write_all(false);

        for (unsigned int AM_lane = 0; AM_lane < NR_AM_BOARDS; ++AM_lane)
        {
            bool read_this_lane = buffer_read_en[AM_lane].read();
            if (read_this_lane & !stub_buffer[AM_lane].empty())
            {
                output_t output_data = stub_buffer[AM_lane].front();
                stub_buffer[AM_lane].pop();
                dv_out[AM_lane].write(true);
                fifo_out[AM_lane].write(output_data);
            }
            else
            {
                fifo_out[AM_lane].write(output_t());
            }
        }
    }

}

// *****************************************************************************
void fifo_manager_datapath::write_neighbours()
{
    while(1)
    {
        wait();

//        for (unsigned int neighbour_out = 0;
//             neighbour_out < NR_NEIGHBOURING_TOWERS;
//             ++neighbour_out)
//        {
//            if (!neighbour_buffer[neighbour_out].empty())
//            {
//                neighbour_dv_out[neighbour_out].write(true);
//                neighbour_stub_out[neighbour_out].write(neighbour_buffer[neighbour_out].front());
//                neighbour_buffer[neighbour_out].pop();
//            }
//            else
//            {
//                neighbour_dv_out[neighbour_out].write(false);
//                neighbour_stub_out[neighbour_out].write(input_stub_t());
//            }
//        }
    }

}

// *****************************************************************************
fifo_manager_datapath::neighbour_vector
fifo_manager_datapath::neighbour_selector(input_stub_t stub) const
{
    neighbour_vector neighbours;

    // todo: this is not real code just for testing purpose
    if (stub.get_strip() < 2)
    {
    	neighbours.push_back(0);
    }

    if (stub.get_strip() > 10)
    {
        neighbours.push_back(1);
    }

    return (neighbours);
}
