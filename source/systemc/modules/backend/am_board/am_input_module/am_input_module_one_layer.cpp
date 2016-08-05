/*!
 * @file am_input_module_one_layer.cpp
 * @author Christian Amstutz
 * @date October 14, 2015
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
        delete_frame("delete_frame"),
        frame_input("frame_input"),
        frame_available("frame_available"),
        frame_empty("frame_empty"),
        frame_processing("frame_processing"),
        stub_stream_output("stream_output")
{
    // ----- Module instance / channel binding ---------------------------------

    // ----- Process registration ----------------------------------------------
    SC_METHOD(read_frames);
        sensitive << frame_input;
        dont_initialize();

    SC_METHOD(update_control_output);
        sensitive << clk.pos();

    SC_METHOD(process_one_frame);
        sensitive << start_process_frame.pos();
        sensitive << delete_frame.pos();
        dont_initialize();

    SC_METHOD(create_stream);
        sensitive << clk.pos();

    // ----- Module variable initialization ------------------------------------

    return;
}

// *****************************************************************************
void am_input_module_one_layer::read_frames()
{
    frame_t in_frame = frame_input.read();
    input_frame_buffer.push(in_frame);

    return;
}

// *****************************************************************************
void am_input_module_one_layer::update_control_output()
{
    if (!input_frame_buffer.empty())
    {
        frame_available.write(true);
        if (input_frame_buffer.back().stub_count() == 0)
        {
            frame_empty.write(true);
        }
        else
        {
            frame_empty.write(false);
        }
    }
    else
    {
        frame_available.write(false);
        frame_empty.write(true);
    }

    return;
}

// *****************************************************************************
void am_input_module_one_layer::process_one_frame()
{
    if ((start_process_frame.read() == true) && (!input_frame_buffer.empty()))
    {
        processed_frame = input_frame_buffer.front();
        input_frame_buffer.pop();

        processed_frame.reset_stub_ptr();
    }
    else if ((delete_frame.read() == true) && (!input_frame_buffer.empty()))
    {
        input_frame_buffer.pop();
    }

    return;
}

// *****************************************************************************
void am_input_module_one_layer::create_stream()
{
    frame_processing.write(false);
    stub_stream_output.write(track_finder::hit_stream::IDLE);

    if (start_process_frame.read() == true)
    {
        stub_stream_output.write(track_finder::hit_stream::START_WORD);

        frame_processing.write(true);

        SYSTEMC_LOG << "Start sending frame "
                    << processed_frame.get_bunch_crossing()
                    << " with " << processed_frame.stub_count()
                    << " stubs to Track Finder";
    }
    else
    {
        frame_t::stub_element_t stub_element;
        if (processed_frame.get_stub(stub_element) == true)
        {
            frame_t::stub_t stub = stub_element.get_stub();
            hit_t hit = get_AM_hit_address(stub);
            stub_stream_output.write(hit);

            SYSTEMC_LOG << stub << "/" << hit;

            frame_processing.write(true);
        }
    }

    return;
}

// *****************************************************************************
am_input_module_one_layer::hit_t am_input_module_one_layer::get_AM_hit_address(
        frame_t::stub_t stub)
{
    hit_t hit = 0x0000;

    hit |= (stub.get_strip()           & 0xFF);
    hit |= (stub.get_fe_chip_ID()      & 0x07) <<  8;
    hit |= (stub.get_concentrator_ID() & 0x01) << 11;
//    hit |= (stub.get_fe_module()       & 0x7F) << 12;
//    hit |= (stub.get_dtc()             & 0x0F) << 19;
//    hit |= (stub.get_prb()             & 0x0F) << 23;
//    hit |= (stub.get_z()               & 0x0F) << 27;

    return hit;
}
