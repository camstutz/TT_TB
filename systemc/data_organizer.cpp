/*!
 * @file data_organizer.cpp
 * @author Christian Amstutz
 * @date Mar 14, 2014
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
 * The module is sensitive to ....
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
        sensitive << clk.pos();
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

        //sc_bv<DC_OUTPUT_WIDTH> input_word = stream_in.at(0).read();
        //input_buffer.write(input_word);
    }
}

// *****************************************************************************
void data_organizer::sort_stubs()
{
    const unsigned int word_width = DC_OUTPUT_WIDTH-2;

    sc_bv<word_width> old_word, new_word;
    unsigned int new_word_pos = 0;
    unsigned int old_word_pos = word_width;

    while (1)
    {
        wait();

        new_word = stream_in[0].read();
        new_word_pos = 0;

        if (stub_table_sel.event()) {
            for(auto& stub_vector : stub_table[stub_table_sel.read()] )
            {
                stub_vector.clear();
            }
            old_word_pos = 0;
        }

        sc_bv<20> process_stub = 0;
        do
        {
            if (old_word_pos < word_width )
            {
                unsigned int bits_from_old = word_width-old_word_pos;

                process_stub(bits_from_old-1,0) = old_word(word_width-1,old_word_pos);
                process_stub(19,bits_from_old) = new_word(19-bits_from_old,0);

                // todo: next line only correct if just one value is read from old_word
                old_word_pos = word_width;
                new_word_pos = 19-bits_from_old+1;
            }
            else
            {
                process_stub = new_word(new_word_pos+20-1,new_word_pos);

                new_word_pos = new_word_pos+20;
            }

            if (process_stub[19] == true)
            {
                unsigned int time_stamp = process_stub(18,16).to_uint();
                stub_table[stub_table_sel.read()][time_stamp].push_back(process_stub(15,0));
            }

        } while (new_word_pos+20 <= word_width );

        old_word = new_word;
        old_word_pos = new_word_pos;
    }

}

// *****************************************************************************
void data_organizer::write_stubs()
{
    while(1)
    {
        wait();

        unsigned int read_table = stub_table_sel.read();
        if (read_table == 0)
        {
            read_table = 1;
        }
        else
        {
            read_table = 0;
        }

        // Reset all outputs
        stub_ext empty_stub;
        empty_stub.set_z_coord(0);
        empty_stub.set_phi_coord(0);
        empty_stub.set_fechip_nr(0);
        empty_stub.set_strip_nr(0);
        do_out_data empty_output;
        empty_output.set_dv(false);
        empty_output.set_data(empty_stub);
        for(auto& out : stub_out)
        {
            out.write(empty_output);
        }

        unsigned int i=0;
        for (auto table_stub : stub_table[stub_table_sel.read()][clock_phase.read().to_uint()])
        {
            do_out_data output_data;

            output_data.set_dv(true);

            stub_ext output_stub;
            output_stub.set_phi_coord(phi);
            output_stub.set_z_coord(z);
            output_stub.set_fechip_nr(table_stub(15,13));
            output_stub.set_strip_nr(table_stub(12,8));
            output_data.set_data(output_stub);

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
            std::cout << sc_time_stamp() << ": [" << j << "]";
            for (unsigned int i=0; i < line.size(); ++i)
            {
                std::cout << line[i] << ",";
            }
            std::cout << std::endl;

            ++j;
        }

   }

}
