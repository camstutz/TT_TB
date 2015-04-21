/*!
 * @file am_input_module_one_layer.cpp
 * @author Christian Amstutz
 * @date April 21, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "am_input_module_one_layer.hpp"

// *****************************************************************************
am_input_module_one_layer::am_input_module_one_layer(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        start_process_frame("start_process_frame"),
        frame_input("frame_input"),
        frame_available("frame_available"),
        frame_processing("frame_processing"),
        stub_stream_output("stream_output")
{
    // ----- Module instance / channel binding ---------------------------------

    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_frames);
        sensitive << frame_input;
    SC_THREAD(update_control_output);
        sensitive << clk.pos();
    SC_THREAD(accept_frame);
        sensitive << start_process_frame.pos();
    SC_THREAD(create_stream);
        sensitive << clk.pos();

    // ----- Module variable initialization ------------------------------------

    return;
}

// *****************************************************************************
void am_input_module_one_layer::read_frames()
{
    while (1)
    {
        wait();

        PRBF_2 in_frame = frame_input.read();
        input_frame_buffer.push(in_frame);
    }
}

// *****************************************************************************
void am_input_module_one_layer::update_control_output()
{
    frame_available.write(false);

    while (1)
    {
        wait();

        if (!input_frame_buffer.empty())
        {
            frame_available.write(true);
        }
        else
        {
            frame_available.write(false);
        }
    }

}

// *****************************************************************************
void am_input_module_one_layer::accept_frame()
{
    while (1)
    {
        wait();

        processed_frame = input_frame_buffer.back();
        input_frame_buffer.pop();

        processed_frame.reset_stub_ptr();
    }

}

// *****************************************************************************
void am_input_module_one_layer::create_stream()
{
    stub_stream_output.write(track_finder::hit_stream(IDLE_EVENT, 0));

    while (1)
    {
        wait();

        frame_processing.write(false);
        stub_stream_output.write(track_finder::hit_stream(IDLE_EVENT, 0));

        if (start_process_frame.read() == true)
        {
            stub_stream_output.write(track_finder::hit_stream(START_EVENT, 0));

            frame_processing.write(true);
        }
        else
        {
            frame_t::stub_element_t stub_element;
            if (processed_frame.get_stub(stub_element) == true)
            {
                frame_t::stub_t stub = stub_element.get_stub();
                hit_t hit = get_AM_hit_address(stub);
                stub_stream_output.write(hit);

                frame_processing.write(true);
            }
        }
    }

}

// *****************************************************************************
am_input_module_one_layer::hit_t am_input_module_one_layer::get_AM_hit_address(
        frame_t::stub_t stub)
{
    hit_t hit = 0x00;

    hit |= (stub.get_strip()           & 0xFF);
    hit |= (stub.get_fe_chip_ID()      & 0x03) << 8;
    hit |= (stub.get_concentrator_ID() & 0x01) << 11;
    hit |= (stub.get_fe_module()       & 0x02) << 12;
    hit |= (stub.get_dtc()             & 0x02) << 14;
    hit |= (stub.get_prb()             & 0x02) << 16;
    hit |= (stub.get_z()               & 0x04) << 18;

    return hit;
}
