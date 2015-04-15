/*!
 * @file data_organizer_one_layer.cpp
 * @author Christian Amstutz
 * @date January 5, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
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
        time_stamp("time_stamp"),
        clock_phase("clock_phase"),
        stub_table_sel("stub_table_sel"),
        stream_in("stream_in"),
        dv(NR_DO_OUT_STUBS, "dv"),
        stub_out(NR_DO_OUT_STUBS, "stub_out"),
        phi("phi"),
        z("z"),
	    input_buffer("input_buffer"),
		dv_sig(NR_DO_OUT_STUBS, "dv_sig"),
	    stub_out_sig(NR_DO_OUT_STUBS, "stub_out_sig"),
	    delay_dv(NR_DO_OUT_STUBS, "delay_dv"),
	    delay_stub_out(NR_DO_OUT_STUBS, "delay_stub_out")
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

    // Make the stub_table the right size
    stub_table.resize(2);
    std::vector<stub_table_type>::iterator stub_table_it = stub_table.begin();
    for (; stub_table_it != stub_table.end(); ++stub_table_it)
    {
        stub_table_it->resize(NR_DC_WINDOW_CYCLES);
    }

    sc_map_linear<sc_delay_signal<bool, DO_output_delay> >::iterator delay_dv_it = delay_dv.begin();
    sc_map_linear<sc_signal<bool> >::iterator dv_sig_it = dv_sig.begin();
    sc_map_linear<sc_out<bool> >::iterator dv_it = dv.begin();
    for (; delay_dv_it != delay_dv.end(); ++delay_dv_it)
    {
    	delay_dv_it->clk.bind(clk);
    	delay_dv_it->input.bind(*dv_sig_it);
    	delay_dv_it->delayed.bind(*dv_it);

    	++dv_sig_it;
    	++dv_it;
    }

    sc_map_linear<sc_delay_signal<do_out_t, DO_output_delay> >::iterator delay_stub_out_it = delay_stub_out.begin();
    sc_map_linear<sc_signal<do_out_t> >::iterator stub_out_sig_it = stub_out_sig.begin();
    sc_map_linear<sc_out<do_out_t> >::iterator stub_out_it = stub_out.begin();
    for (; delay_stub_out_it != delay_stub_out.end(); ++delay_stub_out_it)
    {
    	delay_stub_out_it->clk.bind(clk);
    	delay_stub_out_it->input.bind(*stub_out_sig_it);
    	delay_stub_out_it->delayed.bind(*stub_out_it);

    	++stub_out_sig_it;
    	++stub_out_it;
    }

    return;
}

// *****************************************************************************
void data_organizer_one_layer::read_input()
{
    concat_buffer = 0;
    cc_buf_write_ptr = 0;

    while (1)
    {
        wait();

        dc_out_t input_word = stream_in.read();
        if (input_word.get_header() == 0x02)
        {
            concat_buffer = 0;
            cc_buf_write_ptr = 0;
        }
        input_buffer.write(input_word.get_payload());
    }
}

// *****************************************************************************
void data_organizer_one_layer::sort_stubs()
{
    while (1)
    {
        wait();

        // Clear stub buffer when a new buffer is selected
        if (stub_table_sel.event())
        {
            stub_table_type::iterator stub_vector_it = stub_table[stub_table_sel.read()].begin();
            for(; stub_vector_it != stub_table[stub_table_sel.read()].end(); ++stub_vector_it)
            {
                stub_vector_it->clear();
            }
            cc_buf_write_ptr = 0;
        }

        // Write the input data to the intermediate buffer
        concat_buffer(cc_buf_write_ptr+(dc_out_t::payload_width)-1, cc_buf_write_ptr) = input_buffer.read();
        cc_buf_write_ptr = cc_buf_write_ptr + (dc_out_t::payload_width);

        process_input_buffer();
    }

}

// *****************************************************************************
void data_organizer_one_layer::write_stubs()
{
    while(1)
    {
        wait();

        std::vector<do_stub_t> stub_vector;
        stub_vector = stub_table[!stub_table_sel.read()][clock_phase.read().to_uint()];

        unsigned int output_cnt = 0;
        while (stub_vector.size() != 0)
        {
            do_stub_t output_stub = stub_vector.back();
            stub_vector.pop_back();

            dv_sig[output_cnt].write(true);
            stub_out_sig[output_cnt].write(output_stub);

            ++output_cnt;
        }

        do_stub_t empty_stub;
        while (output_cnt < NR_DO_OUT_STUBS)
        {
            dv_sig[output_cnt].write(false);
            stub_out_sig[output_cnt].write(empty_stub);
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
