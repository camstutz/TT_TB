/*!
 * @file data_concentrator_mpa.cpp
 * @author Christian Amstutz
 * @date December 15, 2014
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
        data_valid(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_MPA_FE_CHIP, "data_valid"),
        fe_stub_in(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_MPA_FE_CHIP, "stub_in"),
        dc_out("dc_out"),
        clock_phase("clock_phase"),
        stub_buffer_write_sel("stub_buffer_write_sel"),
        stub_buffer_read_sel("stub_buffer_read_sel")
{
    // ----- Process registration ------------------------------------------------
    SC_THREAD(controller);
        sensitive << clk.pos();
    SC_THREAD(read_FE_chips);
        sensitive << clk.pos();
    SC_THREAD(write_output);
        sensitive << clk.pos();

    // ----- Module variable initialization --------------------------------------
    
    // ----- Module instance / channel binding -----------------------------------

    stub_buffer.resize(2, stub_buffer_type());

    return;
}

// *****************************************************************************
void data_concentrator_mpa::read_FE_chips()
{
    while(1)
    {
        wait();

        sc_map_square<sc_in<bool> >::iterator data_valid_it = data_valid.begin();
        sc_map_square<sc_in<in_stub_t> >::iterator fe_in_it = fe_stub_in.begin();
        for (; fe_in_it != fe_stub_in.end(); ++fe_in_it)
        {
            if (*data_valid_it == true)
            {
                in_stub_t fe_data = fe_in_it->read();
                std::pair<bool, sc_map_square<sc_in<in_stub_t> >::full_key_type>
                        signal_key = fe_stub_in.get_key(*fe_in_it);
                out_stub_t stub;

                stub.set_valid(true);
                stub.set_bx(calculate_bx(clock_phase.read(), fe_data.get_bx()));
                stub.set_pixel(fe_data.get_pixel());
                stub.set_fechip(signal_key.second.Y_dim);
                stub.set_strip(fe_data.get_strip());
                stub.set_bend(fe_data.get_bend());

                stub_buffer[stub_buffer_write_sel].push_back(stub);
            }

            ++data_valid_it;
        }
    }

}

// *****************************************************************************
void data_concentrator_mpa::controller()
{
    clock_phase.write(0);
    stub_buffer_write_sel.write(0);
    stub_buffer_read_sel.write(0);
    
    while (1)
    {
        wait();

        if (clock_phase.read() == NR_DC_WINDOW_CYCLES-1)
        {
            clock_phase.write(0);
            if(stub_buffer_write_sel.read() == 0)
            {
                stub_buffer_write_sel.write(1);
                stub_buffer_read_sel.write(0);
            }
            else
            {
                stub_buffer_write_sel.write(0);
                stub_buffer_read_sel.write(1);
            }
        }
        else
        {
            clock_phase.write(clock_phase.read()+1);
        }
    }

}

// *****************************************************************************
void data_concentrator_mpa::write_output()
{
    while(1)
    {
        wait();

        if (clock_phase.read() == 0)
        {
            create_output_buffer();
        }

        dc_out_t output_word;
        unsigned int high_buffer_idx;
        unsigned int low_buffer_idx;
        high_buffer_idx = (clock_phase.read()+1)*(dc_out_t::payload_width)-1;
        low_buffer_idx = clock_phase.read()*(dc_out_t::payload_width);
        output_word.set_payload(output_buffer(high_buffer_idx, low_buffer_idx).to_uint());

        sc_bv<DC_OUT_HEADER_BITS> header;
        header[0] = 0;

        // Indicate the beginning of a window by the first bit of a data word
        if (clock_phase.read() == 0)
        {
            header[1] = 1;
        }
        else
        {
            header[1] = 0;
        }

        output_word.set_header(header.to_uint());

        dc_out.write(output_word);
    }

}

// *****************************************************************************
void data_concentrator_mpa::create_output_buffer()
{
    output_buffer = sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES>(0);

    // Buffer size is maximal NR_DC_MPA_OUT_STUBS in real system
    if (stub_buffer[stub_buffer_read_sel].size() > NR_DC_MPA_OUT_STUBS)
    {
        std::cout << sc_time_stamp()
        		  << ": data_concentrator_mpa - Stub buffer overflow!" << std::endl;
    }
    // cut the stubs that are too much for transmission to the back end
    stub_buffer[stub_buffer_read_sel].resize(NR_DC_MPA_OUT_STUBS, out_stub_t());

    for(unsigned short i; i<NR_DC_MPA_OUT_STUBS; i++)
    {
        size_t word_start = i*out_stub_t::total_width;
        size_t word_end = (i+1)*out_stub_t::total_width-1;

        output_buffer(word_end, word_start) = stub_buffer[stub_buffer_read_sel][i].get_bitvector();
    }

    stub_buffer[stub_buffer_read_sel].clear();

    return;
}

// *****************************************************************************
data_concentrator_mpa::out_stub_t::bx_t data_concentrator_mpa::calculate_bx(
		clock_phase_t clock_phase, in_stub_t::bx_t stub_bx)
{
	if (clock_phase % 2 == 0)
	{
		return (stub_bx == 0 ? (clock_phase) : clock_phase+1);
	}
	else
	{
		return (stub_bx == 0 ? (clock_phase-1) : clock_phase);
	}
}
