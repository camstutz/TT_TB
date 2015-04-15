/*!
 * @file dtc_input_unit.cpp
 * @author Christian Amstutz
 * @date April 13, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "dtc_input_unit.hpp"

// *****************************************************************************

const unsigned int dtc_input_unit::fe_collect_cycles = NR_DC_WINDOW_CYCLES;

// *****************************************************************************

/*!
 * @class dtc_input_unit
 *
 * The module is sensitive to ...
 */

dtc_input_unit::dtc_input_unit(sc_module_name _name) :
        sc_module(_name),
        fe_id(0xFF),
        clk("clk"),
        gbt_input("gbt_input"),
        bx_sorted_stubs(fe_collect_cycles, "back_end_link")
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
                CIC::stub_CBC input_stub;
                while (input_frame[in_frame_id].get_stub(input_stub))
                {
                    output_t::stub_t output_stub;

                    output_stub.set_fe_module(fe_id);
                    output_stub.set_concentrator_ID(in_frame_id);

                    output_stub.set_fe_chip_ID(input_stub.get_fe_chip_ID());
                    output_stub.set_strip(input_stub.get_strip());
                    output_stub.set_bend(input_stub.get_bend());

                    output_t output_element;
                    output_element.set_type_field(PRBF::element_type::local_CBC);
                    output_element.set_stub(output_stub);
                    CIC::stub_CBC::bunch_crossing_t bx = input_stub.get_bunch_crossing();
                    bx_sorted_stubs[bx].write(output_element);
                }
            }
            else if (input_frame[in_frame_id].get_header().get_fe_type() == CIC::header::MPA)
            {
                CIC::stub_MPA input_stub;
                while (input_frame[in_frame_id].get_stub(input_stub))
                {
                    output_t::stub_t output_stub;

                    output_stub.set_fe_module(fe_id);
                    output_stub.set_concentrator_ID(in_frame_id);

                    output_stub.set_fe_chip_ID(input_stub.get_fe_chip_ID());
                    output_stub.set_strip(input_stub.get_strip());
                    output_stub.set_bend(input_stub.get_bend());
                    output_stub.set_z(input_stub.get_z());

                    output_t output_element;
                    output_element.set_type_field(PRBF::element_type::local_MPA);
                    output_element.set_stub(output_stub);
                    CIC::stub_CBC::bunch_crossing_t bx = input_stub.get_bunch_crossing();
                    bx_sorted_stubs[bx].write(output_element);
                }
            }
        }
    }

}
