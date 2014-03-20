/*!
 * @file data_organizer.cpp
 * @author Christian Amstutz
 * @date Mar 20, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2013 by Christian Amstutz
 */

#include "data_organizer.hpp"

// *****************************************************************************

/*!
 * @class data_organizer
 *
 * The module is sensitive to clk.pos and the change of the input_buffer.
 */

data_organizer::data_organizer(sc_module_name _name, unsigned int phi,
        unsigned int z) :
        sc_module(_name),
        clk("clk"),
        rst("rst"),
        stream_in(NR_DETECTOR_LAYERS, "stream_in"),
        stub_out(NR_DO_OUT_STUBS, "stub_out"),
        phi(phi),
        z(z)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        sensitive << clk.pos();
    SC_THREAD(read_input);
        sensitive << clk.pos();
    SC_THREAD(sort_stubs);
        sensitive << input_buffer.default_event();
    SC_THREAD(write_stubs);
        sensitive << clk.pos();

    SC_THREAD(print_table);
        sensitive << clk.pos();

    // ----- Module channel/variable initialization ----------------------------
    clock_phase.write(0);
    stub_table_sel.write(0);

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
void data_organizer::controller()
{
    while (1)
    {
        wait();

        sc_bv<DC_OUTPUT_WIDTH> new_word = stream_in[0].read();

        if ((clock_phase.read() == NR_DC_WINDOW_CYCLES-1) ||
                (new_word[DC_OUTPUT_WIDTH-1] == true))
        {
            clock_phase.write(0);
            if(stub_table_sel.read() == 0)
            {
                stub_table_sel.write(1);
            }
            else
            {
                stub_table_sel.write(0);
            }
        }
        else
        {
            clock_phase.write(clock_phase.read()+1);
        }
    }

}

// *****************************************************************************
void data_organizer::read_input()
{
    while (1)
    {
        wait();

        sc_bv<DC_OUTPUT_WIDTH> input_word = stream_in.at(0).read();
        input_buffer.write(input_word(DC_OUTPUT_WIDTH-2-1,0));
    }
}

// *****************************************************************************
void data_organizer::sort_stubs()
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
void data_organizer::write_stubs()
{
    while(1)
    {
        wait();

        // Reset all outputs
        do_out_data empty_output = do_out_data();
        for(auto& out : stub_out)
        {
            out.write(empty_output);
        }

        unsigned int i=0;
        for (auto table_stub : stub_table[!stub_table_sel.read()][clock_phase.read().to_uint()])
        {
            do_out_data::do_stub_t output_stub = do_out_data::do_stub_t(phi, z, table_stub(15,13), table_stub(12,8) );
            do_out_data output_data = do_out_data(true, output_stub);
            stub_out[i].write(output_data);

            ++i;
        }
    }
}

// *****************************************************************************
void data_organizer::print_table()
{
    while(1)
    {
        wait();

        unsigned int j = 0;
        for (auto line : stub_table[0])
        {
            std::cout << sc_time_stamp() << ": [0][" << j << "]";
            for (unsigned int i=0; i < line.size(); ++i)
            {
                std::cout << line[i] << ",";
            }
            std::cout << std::endl;

            ++j;
        }
        j = 0;
        for (auto line : stub_table[1])
        {
            std::cout << sc_time_stamp() << ": [1][" << j << "]";
            for (unsigned int i=0; i < line.size(); ++i)
            {
                std::cout << line[i] << ",";
            }
            std::cout << std::endl;

            ++j;
        }

   }

}
