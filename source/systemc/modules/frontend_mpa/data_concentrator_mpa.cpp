/*!
 * @file data_concentrator_mpa.cpp
 * @author Christian Amstutz
 * @date June 26, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator_mpa.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */

data_concentrator_mpa::data_concentrator_mpa(sc_module_name _name) :
        sc_module(_name) ,
        clk("clk"),
        rst("rst")
//        fe_stub_in(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP, "stub_in"),
//        dc_out("dc_out"),
//        clock_phase("clock_phase"),
//        stub_buffer_write_sel("stub_buffer_write_sel"),
//        stub_buffer_read_sel("stub_buffer_read_sel")
{
//    // ----- Process registration ------------------------------------------------
//    SC_THREAD(controller);
//        sensitive << clk.pos();
//    SC_THREAD(read_FE_chips);
//        sensitive << clk.pos();
//    SC_THREAD(write_output);
//        sensitive << clk.pos();
//
//    // ----- Module variable initialization --------------------------------------
//
//    // ----- Module instance / channel binding -----------------------------------
//
//    stub_buffer.resize(2, stub_buffer_type());

    return;
}

//// *****************************************************************************
//void data_concentrator_cbc::read_FE_chips()
//{
//    while(1)
//    {
//        wait();
//
//        sc_map_square<sc_in<fe_out_data> >::iterator fe_in_it = fe_stub_in.begin();
//        for (; fe_in_it != fe_stub_in.end(); ++fe_in_it)
//        {
//            fe_out_data fe_data = fe_in_it->read();
//            if (fe_data.get_dv() == true)
//            {
//                dc_out_word::dc_stub_t stub;
//                stub.set_timestamp(sc_bv<3>(clock_phase.read()));
//                std::pair<bool, sc_map_square<sc_in<fe_out_data> >::full_key_type> signal_key = fe_stub_in.get_key(*fe_in_it);
//                stub.set_fechip(sc_bv<3>(signal_key.second.Y_dim));
//                stub.set_strip(fe_data.get_data().get_strip());
//                stub.set_bend(fe_data.get_data().get_bend());
//
//                dc_out_word data_word = dc_out_word(true, stub);
//
//                stub_buffer[stub_buffer_write_sel].push_back(data_word);
//            }
//        }
//    }
//
//}
//
//// *****************************************************************************
//void data_concentrator_cbc::controller()
//{
//    clock_phase.write(0);
//    stub_buffer_write_sel.write(0);
//    stub_buffer_read_sel.write(0);
//
//    while (1)
//    {
//        wait();
//
//        if (clock_phase.read() == NR_DC_WINDOW_CYCLES-1)
//        {
//            clock_phase.write(0);
//            if(stub_buffer_write_sel.read() == 0)
//            {
//                stub_buffer_write_sel.write(1);
//                stub_buffer_read_sel.write(0);
//            }
//            else
//            {
//                stub_buffer_write_sel.write(0);
//                stub_buffer_read_sel.write(1);
//            }
//        }
//        else
//        {
//            clock_phase.write(clock_phase.read()+1);
//        }
//    }
//
//}
//
//// *****************************************************************************
//void data_concentrator_cbc::write_output()
//{
//    while(1)
//    {
//        wait();
//
//        if (clock_phase.read() == 0)
//        {
//            create_output_buffer();
//        }
//
//        dc_out_t output_val;
//        unsigned int high_buffer = (clock_phase.read()+1)*(dc_output_data_width)-1;
//        unsigned int low_buffer = clock_phase.read()*(dc_output_data_width);
//        output_val(dc_output_data_upper,0) = output_buffer(high_buffer, low_buffer);
//        output_val[dc_output_debug_pos] = 0;
//
//        // Indicate the beginning of a window by the first bit of a data word
//        if (clock_phase.read() == 0)
//        {
//            output_val[dc_output_valid_pos] = 1;
//        }
//        else
//        {
//            output_val[dc_output_valid_pos] = 0;
//        }
//
//        dc_out.write(output_val);
//    }
//
//}
//
//// *****************************************************************************
//void data_concentrator_cbc::create_output_buffer()
//{
//    output_buffer = sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES>(0);
//
//    // Buffer size is maximal NR_DC_OUT_STUBS in real system
//    if (stub_buffer[stub_buffer_read_sel].size() > NR_DC_OUT_STUBS)
//    {
//        std::cout << "data_concentrator: Stub buffer overflow!" << std::endl;
//    }
//    stub_buffer[stub_buffer_read_sel].resize(NR_DC_OUT_STUBS, dc_out_word());
//
//    for(unsigned short i; i<NR_DC_OUT_STUBS; i++)
//    {
//        output_buffer( (i+1)*dc_out_word::width-1, i*dc_out_word::width) =
//                stub_buffer[stub_buffer_read_sel][i].get_bit_vector();
//    }
//
//    stub_buffer[stub_buffer_read_sel].clear();
//
//    return;
//}
