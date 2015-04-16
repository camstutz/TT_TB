/*!
 * @file do_input_collector.cpp
 * @author Christian Amstutz
 * @date April 16, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "do_input_collector.hpp"

// *****************************************************************************

const unsigned int do_input_collector::dtc_input_nr = 2;

// *****************************************************************************

/*!
 * @class do_input_collector
 *
 * The module is sensitive to ...
 */

do_input_collector::do_input_collector(sc_module_name _name) :
        dtc_inputs(dtc_input_nr, "dtc_inputs"),
        stub_output("stub_output")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_frame);
        dtc_inputs.make_sensitive(sensitive);

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void do_input_collector::process_incoming_frame()
{
    while (1)
    {
        wait();

        unsigned int dtc_id = 0;
        sc_map_linear<sc_in<input_t> >::iterator dtc_input_it = dtc_inputs.begin();
        for(; dtc_input_it != dtc_inputs.end(); ++dtc_input_it)
        {
            if (dtc_input_it->event())
            {
                input_frame_t input_frame = dtc_input_it->read();

                bunch_crossing_t bx = input_frame.get_header().get_bunch_crossing_ID();

                input_frame.reset_stub_ptr();
                input_frame_t::stub_element_t in_stub_element;
                while (input_frame.get_stub(in_stub_element))
                {
                    input_frame_t::stub_element_t::type_field_t  type_field = in_stub_element.get_type_field();
                    output_frame_t::stub_t out_stub(dtc_id, in_stub_element.get_stub());

                    output_frame_t::stub_element_t out_stub_element(type_field, out_stub);
                    output_t output_bx_stub(bx, out_stub_element);

                    stub_output.write(output_bx_stub);
                }
            }

            ++dtc_id;
        }
    }

}

