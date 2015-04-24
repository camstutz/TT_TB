/*!
 * @file data_concentrator_mpa.hpp
 * @author Christian Amstutz
 * @date April 24, 2015
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

#include "../../libraries/systemc_helpers/sc_delay/sc_delay_signal.hpp"
#include "../../libraries/systemc_helpers/sc_map/sc_map.hpp"
#include "../../systems/tt_tb_logger.hpp"
#include "../../systems/TT_configuration.hpp"

#include "../../data_formats/CIC_format/CIC_format.hpp"

/*!
 * @brief
 */
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
class data_concentrator : public sc_module
{
public:
	// ----- Configuration -----------------------------------------------------
	typedef IN_T fe_stub_t;
	typedef CIC_frame output_t;
	typedef OUT_STUB_T output_stub_t;

	static const unsigned int nr_fe_chips;
	static const unsigned int max_in_stubs_per_cycle;
	static const unsigned int collection_cycles;
	static const unsigned int max_output_stubs;
	static const unsigned int output_window_cycles;

	// -------------------------------------------------------------------------

    typedef std::vector<output_stub_t> stub_buffer_type;
    typedef output_t::header_t::bunch_crossing_t bunch_crossing_t;
    typedef unsigned int clock_phase_t;

    // ----- Port Declarations -------------------------------------------------
    sc_in<bool> clk;
    sc_map_square<sc_in<bool> > data_valid;
    sc_map_square<sc_in<fe_stub_t> > fe_stub_in;
    sc_out<output_t> dc_out;

    // ----- Local Channel Declarations ----------------------------------------
    sc_signal<bunch_crossing_t> LHC_bunch_crossing;
    sc_signal<clock_phase_t> clock_phase;
    std::vector<stub_buffer_type> stub_buffer;
    sc_signal<output_t> dc_out_sig;

    /** Control signal that switches between the two stub tables */
    sc_signal<bool> stub_buffer_write_sel;
    sc_signal<bool> stub_buffer_read_sel;

    // ----- Process Declarations ----------------------------------------------
    void controller();
    void read_FE_chips();
    void write_output();

    // ----- Other Method Declarations -----------------------------------------
    output_t create_output_buffer();

    // ----- Module Instantiations ---------------------------------------------
    sc_delay_signal<output_t, DC_output_delay> delay_output;

    // ----- Constructor -------------------------------------------------------
    data_concentrator(sc_module_name _name);
    SC_HAS_PROCESS(data_concentrator);

private:
    typename output_stub_t::bunch_crossing_t calculate_bx(clock_phase_t clock_phase, typename fe_stub_t::bx_t stub_bx);
};

// *****************************************************************************

typedef data_concentrator<fe_cbc_stub_t, NR_FE_CHIP_PER_MODULE,
        MAX_HITS_PER_CBC_FE_CHIP, COLLECTION_CYCLES_CBC_FE_CHIP, CIC::stub_CBC,
        NR_DC_CBC_OUT_STUBS, NR_DC_WINDOW_CYCLES> data_concentrator_cbc;

typedef data_concentrator<fe_mpa_stub_t, NR_FE_CHIP_PER_MODULE,
        MAX_HITS_PER_MPA_FE_CHIP, COLLECTION_CYCLES_MPA_FE_CHIP, CIC::stub_MPA,
        NR_DC_MPA_OUT_STUBS, NR_DC_WINDOW_CYCLES> data_concentrator_mpa;

// *****************************************************************************

// *****************************************************************************

template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::nr_fe_chips = NR_FE_CHIP_PER_SIDE;

template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::max_in_stubs_per_cycle = MAX_IN_STUBS_PER_CYCLE;

template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::collection_cycles = IN_COLLECTION_CYCLES;

template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::max_output_stubs = MAX_OUT_STUBS;

template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
const unsigned int data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::output_window_cycles = COLLECTION_CYCLES;

// *****************************************************************************
/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::data_concentrator(sc_module_name _name) :
        sc_module(_name) ,
        clk("clk"),
        data_valid(nr_fe_chips, max_in_stubs_per_cycle, "data_valid"),
        fe_stub_in(nr_fe_chips, max_in_stubs_per_cycle, "fe_stub_in"),
        dc_out("dc_out"),
        clock_phase("clock_phase"),
        stub_buffer_write_sel("stub_buffer_write_sel"),
        stub_buffer_read_sel("stub_buffer_read_sel"),
		delay_output("delay_outout")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(controller);
        sensitive << clk.pos();
    SC_THREAD(read_FE_chips);
        sensitive << clk.pos();
    SC_THREAD(write_output);
        sensitive << clk.pos();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    delay_output.clk.bind(clk);
    delay_output.input.bind(dc_out_sig);
    delay_output.delayed.bind(dc_out);

    stub_buffer.resize(2, stub_buffer_type());

    clock_phase.write(0);
    stub_buffer_write_sel.write(0);
    stub_buffer_read_sel.write(1);

    return;
}

// *****************************************************************************
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::read_FE_chips()
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

                output_stub_t stub;
                stub.set_strip(fe_data.get_strip());
                stub.set_bend(fe_data.get_bend());
                stub.set_bunch_crossing(calculate_bx(clock_phase.read(), fe_data.get_bx()));
                stub.set_fe_chip_ID(signal_key.second.Y_dim);

                stub_buffer[stub_buffer_write_sel].push_back(stub);
            }

            ++data_valid_it;
        }
    }

}

// *****************************************************************************
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::controller()
{
    LHC_bunch_crossing.write(0);

    while (1)
    {
        wait();

        LHC_bunch_crossing.write(LHC_bunch_crossing.read() + 1);

        if (clock_phase.read() == output_window_cycles-1)
        {
            clock_phase.write(0);
            stub_buffer_write_sel.write( !stub_buffer_write_sel.read() );
            stub_buffer_read_sel.write( !stub_buffer_read_sel.read() );
        }
        else
        {
            clock_phase.write(clock_phase.read()+1);
        }
    }

}

// *****************************************************************************
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
void data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::write_output()
{
    while(1)
    {
        wait();

        if (clock_phase.read() == 0)
        {
            output_t output_frame = create_output_buffer();
            dc_out_sig.write(output_frame);

            if (output_frame.stub_count())
            {
                SYSTEMC_LOG << "Frame " << output_frame.get_header().get_bunch_crossing() << " transmitted.";
            }
        }
    }

}

// *****************************************************************************
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
typename data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::output_t data_concentrator<IN_T, NR_FE_CHIPS,
        MAX_IN_STUBS_PER_CYCLE, IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::create_output_buffer()
{
    output_t::header_t output_header;
    // TODO: output_header.set_fe_type();
    output_header.set_hw_status(output_t::header_t::status_OK);
    output_header.set_bunch_crossing(LHC_bunch_crossing.read());

    output_t output_frame;
    output_frame.set_header(output_header);

    if (stub_buffer[stub_buffer_read_sel].size() > max_output_stubs)
    {
        std::cerr << sc_time_stamp()
        		  << ": data_concentrator - Stub buffer overflow! ("
        		  << stub_buffer[stub_buffer_read_sel].size() << "/"
        		  <<  max_output_stubs<< ")" << std::endl;
    }
    // cut the stubs that are too much for transmission to the back end
    // TODO: cut stubs by bend
    if (stub_buffer[stub_buffer_read_sel].size() > max_output_stubs)
    {
        stub_buffer[stub_buffer_read_sel].resize(max_output_stubs, output_stub_t());
    }

    typename stub_buffer_type::iterator stub_buffer_it = stub_buffer[stub_buffer_read_sel].begin();
    for(; stub_buffer_it != stub_buffer[stub_buffer_read_sel].end(); ++stub_buffer_it)
    {
        output_frame.add_stub(*stub_buffer_it);
    }

    stub_buffer[stub_buffer_read_sel].clear();

    return output_frame;
}

// *****************************************************************************
template <typename IN_T, unsigned int NR_FE_CHIPS,
        unsigned int MAX_IN_STUBS_PER_CYCLE, unsigned int IN_COLLECTION_CYCLES,
        typename OUT_STUB_T, unsigned int MAX_OUT_STUBS,
        unsigned int COLLECTION_CYCLES>
typename data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::output_stub_t::bunch_crossing_t
data_concentrator<IN_T, NR_FE_CHIPS, MAX_IN_STUBS_PER_CYCLE,
        IN_COLLECTION_CYCLES, OUT_STUB_T, MAX_OUT_STUBS,
        COLLECTION_CYCLES>::calculate_bx(clock_phase_t clock_phase,
		typename fe_stub_t::bx_t stub_bx)
{
    // TODO: take the real configuration value for collection cycles
    unsigned int fe_collection_cycles = pow(2, fe_stub_t::bx_width);

    return (fe_collection_cycles * (clock_phase / fe_collection_cycles) + stub_bx);
}
