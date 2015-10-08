/*!
 * @file data_concentrator.cpp
 * @author Christian Amstutz
 * @date October 6, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "data_concentrator.hpp"

// *****************************************************************************
/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */
data_concentrator::data_concentrator(sc_module_name _name, data_concentrator_config configuration) :
        sc_module(_name),
        configuration(configuration),
        nr_fe_chips(configuration.fe_chips_count),
        max_in_stubs_per_cycle(configuration.frontend_chip_type.max_stubs_per_cycle),
        collection_cycles(configuration.frontend_chip_type.collection_cycles),
        max_output_stubs(configuration.max_output_stubs),
        output_window_cycles(configuration.output_window_cycles),
        clk("clk"),
        data_valid(nr_fe_chips, max_in_stubs_per_cycle, "data_valid"),
        fe_stub_in(nr_fe_chips, max_in_stubs_per_cycle, "fe_stub_in"),
        dc_out("dc_out"),
        clock_phase("clock_phase"),
        stub_buffer_write_sel("stub_buffer_write_sel"),
        stub_buffer_read_sel("stub_buffer_read_sel"),
        delay_output("delay_output", configuration.delay_cycles),
        output_stub_config(configuration.output_stub)
{
    // ----- Process registration ----------------------------------------------
    SC_METHOD(controller);
        sensitive << clk.pos();
        dont_initialize();
    SC_METHOD(read_FE_chips);
        sensitive << clk.pos();
        dont_initialize();
    SC_METHOD(write_output);
        sensitive << clk.pos();
        dont_initialize();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------
    delay_output.clk.bind(clk);
    delay_output.input.bind(dc_out_sig);
    delay_output.delayed.bind(dc_out);

    stub_buffer.resize(2, stub_buffer_type());

    LHC_bunch_crossing.write(0);
    clock_phase.write(0);
    stub_buffer_write_sel.write(0);
    stub_buffer_read_sel.write(1);

    return;
}

// *****************************************************************************
void data_concentrator::read_FE_chips()
{
    sc_map_square<sc_in<bool> >::iterator data_valid_it = data_valid.begin();
    typename sc_map_square<sc_in<fe_stub_t> >::iterator fe_in_it = fe_stub_in.begin();
    for (; fe_in_it != fe_stub_in.end(); ++fe_in_it)
    {
        if (*data_valid_it == true)
        {
            fe_stub_t fe_data = fe_in_it->read();
            std::pair<bool, typename sc_map_square<sc_in<fe_stub_t> >::key_type>
                    signal_key = fe_stub_in.get_key(*fe_in_it);

            output_stub_t stub(output_stub_config);
            stub.set_strip(fe_data.get_strip());
            stub.set_bend(fe_data.get_bend());
            stub.set_bx(calculate_bx(clock_phase.read(), fe_data.get_bx()));

            stub.set_fechip(signal_key.second.Y);

            stub_buffer[stub_buffer_write_sel].push_back(stub);
        }

        ++data_valid_it;
    }

    return;
}

// *****************************************************************************
void data_concentrator::controller()
{
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

    return;
}

// *****************************************************************************
void data_concentrator::write_output()
{
    if (clock_phase.read() == 0)
    {
        output_t output_frame = create_output_buffer();
        dc_out_sig.write(output_frame);

        if (output_frame.stub_count() > 0)
        {
            SYSTEMC_LOG << "Frame @ bx=" << output_frame.get_header().get_bunch_crossing()
                        << " with "
                        << output_frame.get_header().get_stub_count() << " stubs transmitted.";
        }
    }

    return;
}

// *****************************************************************************
typename data_concentrator::output_t data_concentrator::create_output_buffer()
{
    output_t::header_t output_header;
    // TODO: output_header.set_fe_type();
    output_header.set_hw_status(output_t::header_t::status_OK);
    output_header.set_bunch_crossing(LHC_bunch_crossing.read() - output_window_cycles);
    if (configuration.output_stub.pixel_bits > 0)
    {
        output_header.set_fe_type(CIC::header::MPA);
    }
    else
    {
        output_header.set_fe_type(CIC::header::CBC);
    }

    output_t output_frame(output_stub_config);
    output_frame.set_header(output_header);

    if (stub_buffer[stub_buffer_read_sel].size() > max_output_stubs)
    {
        SYSTEMC_LOG << "Stub buffer overflow! ("
                    << stub_buffer[stub_buffer_read_sel].size() << "/"
                    << max_output_stubs<< ")";
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
typename data_concentrator::output_stub_t::bx_t
inline data_concentrator::calculate_bx(clock_phase_t clock_phase,
        typename fe_stub_t::bx_t stub_bx)
{
    unsigned int slot_start = collection_cycles * (clock_phase / collection_cycles);

    return slot_start + stub_bx;
}
