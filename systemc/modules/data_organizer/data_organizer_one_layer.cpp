/*!
 * @file data_organizer_one_layer.cpp
 * @author Christian Amstutz
 * @date Apr 20, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#include "data_organizer_one_layer.hpp"

// *****************************************************************************

/*!
 * @class data_organizer
 *
 * The module is sensitive to clk.pos and the change of the input_buffer.
 */

data_organizer_one_layer::data_organizer_one_layer(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        time_stamp("time_stamp"),
        clock_phase("clock_phase"),
        stub_table_sel("stub_table_sel"),
        stream_in("stream_in"),
        stub_out(NR_DO_OUT_STUBS, "stub_out"),
        phi("phi"),
        z("z")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << clk.pos();
    SC_THREAD(sort_stubs);
        sensitive << input_buffer.default_event();
    SC_THREAD(write_stubs);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void data_organizer_one_layer::read_input()
{
    while (1)
    {
        wait();

        sc_bv<DC_OUTPUT_WIDTH> input_word = stream_in.read();
        input_buffer.write(input_word(DC_OUTPUT_WIDTH-2-1,0));
    }
}

// *****************************************************************************
void data_organizer_one_layer::sort_stubs()
{
    sc_bv<DC_OUTPUT_WIDTH+16> concat_buffer;

    concat_buffer = 0;
    unsigned int cc_buf_write_ptr = 0;

    while (1)
    {
        wait();

        if (stub_table_sel.event()) {
            for(auto& stub_vector : stub_table[stub_table_sel.read()] )
            {
                stub_vector.clear();
            }
            cc_buf_write_ptr = 0;
        }

        concat_buffer(cc_buf_write_ptr+(DC_OUTPUT_WIDTH-2)-1, cc_buf_write_ptr) = input_buffer.read();
        cc_buf_write_ptr = cc_buf_write_ptr+(DC_OUTPUT_WIDTH-2);

        do
        {
            sc_bv<20> process_stub = concat_buffer(19,0);
            if (process_stub[19] == true)
            {
                unsigned int time_stamp = process_stub(18,16).to_uint();
                stub_table[stub_table_sel.read()][time_stamp].push_back(process_stub(15,0));
            }

            concat_buffer = concat_buffer(DC_OUTPUT_WIDTH+16-1,20);
            cc_buf_write_ptr = cc_buf_write_ptr - 20;

        } while (cc_buf_write_ptr >= 20);
    }

}

// *****************************************************************************
void data_organizer_one_layer::write_stubs()
{
    while(1)
    {
        wait();

        auto stub_vector = stub_table[!stub_table_sel.read()][clock_phase.read().to_uint()];

        unsigned int output_cnt = 0;
      	while (stub_vector.size() != 0)
        {
            do_out_data::do_stub_t output_stub;
           	auto actual_stub = stub_vector.back();
            stub_vector.pop_back();
            sc_bv<3> fe_chip = actual_stub(15,13);
            sc_bv<5> superstrip = actual_stub(12,8);
           	output_stub.set_phi(phi.read());
           	output_stub.set_z(z.read());
           	output_stub.set_fechip(fe_chip);
           	output_stub.set_strip(superstrip);
           	do_out_data output_data;
           	output_data.set_dv(true);
           	output_data.set_data(actual_stub);
            stub_out[output_cnt].write(output_data);

            ++output_cnt;
         }
    }

}

//// *****************************************************************************
//void data_organizer_one_layer::print_table()
//{
//    while(1)
//    {
//        wait();
//
//        unsigned int j = 0;
//        for (auto line : stub_table[0])
//        {
//            std::cout << sc_time_stamp() << ": [0][" << j << "]";
//            for (unsigned int i=0; i < line.size(); ++i)
//            {
//                std::cout << line[i] << ",";
//            }
//            std::cout << std::endl;
//
//            ++j;
//        }
//        j = 0;
//        for (auto line : stub_table[1])
//        {
//            std::cout << sc_time_stamp() << ": [1][" << j << "]";
//            for (unsigned int i=0; i < line.size(); ++i)
//            {
//                std::cout << line[i] << ",";
//            }
//            std::cout << std::endl;
//
//            ++j;
//        }
//
//   }
//
//}
