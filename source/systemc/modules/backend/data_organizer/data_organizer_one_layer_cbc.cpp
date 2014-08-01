/*!
 * @file data_organizer_one_layer_cbc.cpp
 * @author Christian Amstutz
 * @date July 31, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_organizer_one_layer_cbc.hpp"

// *****************************************************************************

/*!
 * @class data_organizer_one_layer_mpa
 *
 * The module is sensitive to clk.pos and the change of the input_buffer.
 */

data_organizer_one_layer_cbc::data_organizer_one_layer_cbc(sc_module_name _name) :
        data_organizer_one_layer(_name)
{
    // ----- Process registration ----------------------------------------------

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void data_organizer_one_layer_cbc::process_input_buffer()
{
    do
    {
        cbc_out_stub_t process_stub;
        process_stub.set_bitvector(concat_buffer(cbc_out_stub_t::total_width-1,0));
        if (process_stub.get_valid() == true)
        {
            unsigned int time_stamp = process_stub.get_bx();
            do_stub_t output_stub;
            output_stub.set_phi(phi);
            output_stub.set_z(z);
            output_stub.set_fechip(process_stub.get_fechip());
            // Superstrip generation
            output_stub.set_strip(process_stub.get_strip() >> (cbc_out_stub_t::strip_width - do_stub_t::strip_width));
            stub_table[stub_table_sel.read()][time_stamp].push_back(output_stub);
        }

        concat_buffer = concat_buffer(2*dc_out_t::total_width-1, cbc_out_stub_t::total_width);
        cc_buf_write_ptr = cc_buf_write_ptr - cbc_out_stub_t::total_width;

    } while (cc_buf_write_ptr >= cbc_out_stub_t::total_width);

    return;
}