/*!
 * @file data_concentrator_mpa.hpp
 * @author Christian Amstutz
 * @date February 23, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>
#include <utility>

#include <systemc.h>

#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../libraries/systemc_helpers/nbits.hpp"

#include "../../systems/TT_configuration.hpp"

/*!
 * @brief
 */
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
class data_concentrator : public sc_module
{
public:
	// ----- Configuration -----------------------------------------------------
	typedef IN_STUB_T fe_stub_t;
	typedef OUT_STUB_T output_stub_t;

	static const unsigned int nr_fe_chips;
	static const unsigned int max_stubs_per_cycle;
	static const unsigned int collection_cycles;
	static const unsigned int total_collected_stubs;
	static const unsigned int output_width;
	static const unsigned int output_window_cycles;

	// -------------------------------------------------------------------------

    typedef dc_out_t output_stream_t;

    typedef std::vector<output_stub_t> stub_buffer_type;
    typedef unsigned int clock_phase_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_square<sc_in<bool> > data_valid;
    sc_map_square<sc_in<fe_stub_t> > fe_stub_in;
    sc_out<output_stream_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<clock_phase_t> clock_phase;
    sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES> output_buffer;
    std::vector<stub_buffer_type> stub_buffer;

    /** Control signal that switches between the two stub tables */
    sc_signal<unsigned int> stub_buffer_write_sel;
    sc_signal<unsigned int> stub_buffer_read_sel;

    // ----- Process Declarations ----------------------------------------------
    void controller();
    void read_FE_chips();
    void write_output();

    // ----- Other Method Declarations -----------------------------------------

    // ----- Module Instantiations ---------------------------------------------

    // ----- Constructor -------------------------------------------------------
    data_concentrator(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator);

private:
    void create_output_buffer();
    typename output_stub_t::bx_t calculate_bx(clock_phase_t clock_phase,
            typename fe_stub_t::bx_t stub_bx);
};

// *****************************************************************************

// *****************************************************************************

// TODO: Add this parameter to template
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::nr_fe_chips = 8;

template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::max_stubs_per_cycle = MAX_STUBS_PER_CYCLE;

template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::collection_cycles = COLLECTION_CYCLES;

template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::total_collected_stubs = MAX_STUBS_PER_CYCLE * COLLECTION_CYCLES;

template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::output_width = DC_OUTPUT_WIDTH;

template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::output_window_cycles = NR_DC_WINDOW_CYCLES;

// *****************************************************************************
/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::data_concentrator(sc_module_name _name) :
        sc_module(_name) ,
        clk("clk"),
        data_valid(nr_fe_chips, max_stubs_per_cycle, "data_valid"),
        fe_stub_in(nr_fe_chips, max_stubs_per_cycle, "fe_stub_in"),
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
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::read_FE_chips()
{
    while(1)
    {
        wait();

        sc_map_square<sc_in<bool> >::iterator data_valid_it = data_valid.begin();
        typename sc_map_square<sc_in<fe_stub_t> >::iterator fe_in_it = fe_stub_in.begin();
        for (; fe_in_it != fe_stub_in.end(); ++fe_in_it)
        {
            if (*data_valid_it == true)
            {
                fe_stub_t fe_data = fe_in_it->read();
                std::pair<bool, typename sc_map_square<sc_in<fe_stub_t> >::full_key_type>
                        signal_key = fe_stub_in.get_key(*fe_in_it);

                output_stub_t stub(fe_data);
                stub.set_valid(true);
                stub.set_bx(calculate_bx(clock_phase.read(), fe_data.get_bx()));
                stub.set_fechip(signal_key.second.Y_dim);

                stub_buffer[stub_buffer_write_sel].push_back(stub);
            }

            ++data_valid_it;
        }
    }

}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::controller()
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
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::write_output()
{
    while(1)
    {
        wait();

        if (clock_phase.read() == 0)
        {
            create_output_buffer();
        }

        output_stream_t output_word;
        unsigned int high_buffer_idx;
        unsigned int low_buffer_idx;
        high_buffer_idx = (clock_phase.read()+1)*(output_stream_t::payload_width)-1;
        low_buffer_idx = clock_phase.read()*(output_stream_t::payload_width);
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
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::create_output_buffer()
{
    output_buffer = sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES>(0);

    // Buffer size is maximal NR_DC_MPA_OUT_STUBS in real system
    if (stub_buffer[stub_buffer_read_sel].size() > max_stubs_per_cycle)
    {
        std::cout << sc_time_stamp()
        		  << ": data_concentrator_mpa - Stub buffer overflow!" << std::endl;
    }
    // cut the stubs that are too much for transmission to the back end
    stub_buffer[stub_buffer_read_sel].resize(max_stubs_per_cycle, output_stub_t());

    for(unsigned short i; i<max_stubs_per_cycle; i++)
    {
        size_t word_start = i*output_stub_t::total_width;
        size_t word_end = (i+1)*output_stub_t::total_width-1;

        output_buffer(word_end, word_start) = stub_buffer[stub_buffer_read_sel][i].get_bitvector();
    }

    stub_buffer[stub_buffer_read_sel].clear();

    return;
}

// *****************************************************************************
template <typename IN_STUB_T, typename OUT_STUB_T,
          unsigned int MAX_STUBS_PER_CYCLE, unsigned int COLLECTION_CYCLES>
typename data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::output_stub_t::bx_t
		data_concentrator<IN_STUB_T,OUT_STUB_T, MAX_STUBS_PER_CYCLE, COLLECTION_CYCLES>::calculate_bx(clock_phase_t clock_phase, typename fe_stub_t::bx_t stub_bx)
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

