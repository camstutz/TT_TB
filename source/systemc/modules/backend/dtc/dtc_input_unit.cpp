/*!
 * @file dtc_input_unit.cpp
 * @author Christian Amstutz
 * @date July 29, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_input_unit.hpp"

// *****************************************************************************

/*!
 * @class dtc_input_unit
 *
 * The module is sensitive to ...
 */

dtc_input_unit::dtc_input_unit(sc_module_name _name,
        dtc_input_unit_config configuration) :
        sc_module(_name),
        fe_collect_cycles(configuration.fe_collect_cycles),
        fe_id(configuration.fe_id),
        clk("clk"),
        gbt_input("gbt_input"),
        write_buffer_select("write_buffer_select"),
        bx_buffer_out(2, fe_collect_cycles, "bx_sorted_stubs"),
        configuration(configuration)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(process_stubs);
        sensitive << gbt_input;

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void dtc_input_unit::process_stubs()
{
    while (1)
    {
        wait();

        input_t input_data = gbt_input.read();

        input_frame_t input_frame[2];
        input_frame[0] = input_data.get_left();
        input_frame[1] = input_data.get_right();

        for (unsigned int in_frame_id = 0; in_frame_id < 2; ++in_frame_id)
        {
            if (input_frame[in_frame_id].get_header().get_fe_type() == CIC::header::CBC)
            {
                unsigned int stub_nr = input_frame[in_frame_id].stub_count();
                if (stub_nr > 0)
                {
                    SYSTEMC_LOG << "CBC frame with " << stub_nr << " stubs received.";
                }

                stub input_stub(configuration.CBC_input_stub);
                while (input_frame[in_frame_id].get_stub(input_stub))
                {
                    output_element_t::stub_t output_stub;

                    output_stub.set_fe_module(fe_id);
                    output_stub.set_concentrator_ID(in_frame_id);
                    output_stub.set_fe_chip_ID(input_stub.get_fechip());
                    output_stub.set_strip(input_stub.get_strip());
                    output_stub.set_bend(input_stub.get_bend());

                    output_element_t output_element;
                    output_element.set_type_field(PRBF::element_type::local_CBC);
                    output_element.set_stub(output_stub);

                    dtc_buffer_element::first_type frame_bx, relative_bx;
                    frame_bx = input_frame[in_frame_id].get_header().get_bunch_crossing();
                    relative_bx = input_stub.get_bx();
                    dtc_buffer_element buffer_element;
                    buffer_element.first = frame_bx + relative_bx;
                    buffer_element.second = output_element;

                    bx_buffer_out.at(write_buffer_select.read(), relative_bx).write(buffer_element);
                }
            }
            else if (input_frame[in_frame_id].get_header().get_fe_type() == CIC::header::MPA)
            {
                unsigned int stub_nr = input_frame[in_frame_id].stub_count();
                if (stub_nr > 0)
                {
                    SYSTEMC_LOG << "MPA frame with " << stub_nr << " stubs received.";
                }

                stub input_stub(configuration.MPA_input_stub);
                while (input_frame[in_frame_id].get_stub(input_stub))
                {
                    output_element_t::stub_t output_stub;

                    output_stub.set_fe_module(fe_id);
                    output_stub.set_concentrator_ID(in_frame_id);

                    output_stub.set_fe_chip_ID(input_stub.get_fechip());
                    output_stub.set_strip(input_stub.get_strip());
                    output_stub.set_bend(input_stub.get_bend());
                    output_stub.set_z(input_stub.get_pixel());

                    output_element_t output_element;
                    output_element.set_type_field(PRBF::element_type::local_MPA);
                    output_element.set_stub(output_stub);

                    dtc_buffer_element::first_type frame_bx, relative_bx;
                    frame_bx = input_frame[in_frame_id].get_header().get_bunch_crossing();
                    relative_bx = input_stub.get_bx();
                    dtc_buffer_element buffer_element;
                    buffer_element.first = frame_bx + relative_bx;
                    buffer_element.second = output_element;

                    bx_buffer_out.at(write_buffer_select.read(), relative_bx).write(buffer_element);
                }
            }
        }
    }

}
