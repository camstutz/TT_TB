/*!
 * @file do_input_collector.hpp
 * @author Christian Amstutz
 * @date August 17, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include "../../../data_formats/prbf/PRBF.hpp"
#include "../../../data_formats/sc_pair/sc_pair.hpp"
#include "../../../systems/tt_tb_logger.hpp"
#include "input_collector_config.hpp"

#include "sc_map.hpp"

#include <systemc.h>

/*!
 * @brief
 */
template <typename IN_FRAME, typename OUT_FRAME>
class input_collector : public sc_module
{
public:
    typedef IN_FRAME input_frame_t;
    typedef input_frame_t input_t;
    typedef OUT_FRAME output_frame_t;
    typedef typename input_frame_t::header_t::bunch_crossing_ID_t bunch_crossing_t;
    typedef sc_pair<bunch_crossing_ID_type, typename output_frame_t::stub_element_t> output_pair_t;
    typedef output_pair_t output_t;

    const unsigned int input_nr;

// ----- Port Declarations -----------------------------------------------------
    sc_map_linear<sc_in<input_t> > frame_inputs;

    sc_fifo_out<output_t> stub_output;

// ----- Local Channel Declarations --------------------------------------------

// ----- Local Storage Declarations --------------------------------------------

// ----- Process Declarations --------------------------------------------------
    void process_incoming_frame();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    input_collector(sc_module_name _name, input_collector_config configuration);
    SC_HAS_PROCESS(input_collector);
};

// *****************************************************************************

// *****************************************************************************

/*!
 * @class input_collector
 *
 * The module is sensitive to ...
 */

template <typename IN_FRAME, typename OUT_FRAME>
input_collector<IN_FRAME, OUT_FRAME>::input_collector(sc_module_name _name,
        input_collector_config configuration) :
        sc_module(_name),
        input_nr(configuration.input_nr),
        frame_inputs(input_nr, "frame_inputs"),
        stub_output("stub_output")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_incoming_frame);
        sensitive << frame_inputs;

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <typename IN_FRAME, typename OUT_FRAME>
void input_collector<IN_FRAME, OUT_FRAME>::process_incoming_frame()
{
    while (1)
    {
        wait();

        unsigned int dtc_id = 0;
        typename sc_map_linear<sc_in<input_t> >::iterator input_it = frame_inputs.begin();
        for(; input_it != frame_inputs.end(); ++input_it)
        {
            if (input_it->event())
            {
                input_frame_t input_frame = input_it->read();

                if (input_frame.stub_count() > 0)
                {
                    SYSTEMC_LOG << "Frame " << input_frame.get_bunch_crossing()
                            << " @ input " << input_it.get_key().second
                            << " with " << input_frame.stub_count() << " stubs reveived.";
                }

                bunch_crossing_t bx = input_frame.get_header().get_bunch_crossing_ID();

                input_frame.reset_stub_ptr();
                typename input_frame_t::stub_element_t in_stub_element;
                while (input_frame.get_stub(in_stub_element))
                {
                    typename input_frame_t::stub_element_t::type_field_t  type_field = in_stub_element.get_type_field();
                    typename output_frame_t::stub_t out_stub(dtc_id, in_stub_element.get_stub());

                    typename output_frame_t::stub_element_t out_stub_element(type_field, out_stub);
                    output_t output_bx_stub(bx, out_stub_element);

                    stub_output.write(output_bx_stub);
                }
            }
            ++dtc_id;
        }
    }

}
