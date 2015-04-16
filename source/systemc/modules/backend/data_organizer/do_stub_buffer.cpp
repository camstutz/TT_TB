/*!
 * @file do_stub_buffer.cpp
 * @author Christian Amstutz
 * @date April 16, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "do_stub_buffer.hpp"

// *****************************************************************************

/*!
 * @class do_stub_buffer
 *
 * The module is sensitive to ...
 */

do_stub_buffer::do_stub_buffer(sc_module_name _name) :
        stub_input("stub_input"),
        bunch_crossing_select("bunch_crossing_select"),
        stub_output("stub_output")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(write_frame);
        sensitive << stub_input.data_written();
    SC_THREAD(read_frame);
        sensitive << bunch_crossing_select;

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void do_stub_buffer::write_frame()
{
    while (1)
    {
        wait();

        while (stub_input.num_available() > 0)
        {
            input_pair input_stub = stub_input.read();
            bx_buffer[input_stub.first].push_back(input_stub.second);
        }
    }

}

// *****************************************************************************
void do_stub_buffer::read_frame()
{
    while (1)
    {
        wait();

        bunch_crossing_t bx = bunch_crossing_select.read();

        if (bx_buffer.find(bx) != bx_buffer.end())
        {
            std::vector<element_t> stub_vector = bx_buffer[bx];
            std::vector<element_t>::iterator stub_it = stub_vector.begin();
            for (; stub_it != stub_vector.end(); ++stub_it)
            {
                stub_output.write(*stub_it);
            }

            // delete bunch crossing entry
            bx_buffer.erase(bx);
        }
    }

}

// *****************************************************************************
do_stub_buffer::input_pair::input_pair() :
        pair(index_t(), element_t())
{}

// *****************************************************************************
do_stub_buffer::input_pair::input_pair(index_t index, element_t element) :
        pair(index, element)
{}

// *****************************************************************************
std::ostream& operator<< (std::ostream& stream, const do_stub_buffer::input_pair& pair)
{
    stream << "[";
    stream << pair.first;
    stream << ",";
    stream << pair.second;
    stream << "]";

    return stream;
}
