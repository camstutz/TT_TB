/*!
 * @file hit_generator_tb.cpp
 * @author Christian Amstutz
 * @date August 20, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "hit_generator_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class hit_generator_tb
 * The module is sensitive to ...
 */

hit_generator_tb::hit_generator_tb(const sc_module_name _name, const track_trigger_config configuration) :
        sc_module(_name),
        hit_signals(configuration.hit_generator.chip_addresses, "hit_signals"),
        hit_cnt_signal("hit_cnt_signal"),
        dut_hit_generator("Hit_Generator_DUT", configuration.hit_generator),
        configuration(configuration.hit_generator)
{
    // ----- Creation and binding of signals -----------------------------------
    dut_hit_generator.stub_outputs(hit_signals);
    dut_hit_generator.hit_cnt.bind(hit_cnt_signal);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(check_output);
    for (auto& hit_signal : hit_signals)
    {
        sensitive << hit_signal.data_written_event();
    }

    SC_THREAD(check_hit_counter);
        sensitive << hit_cnt_signal;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
               << "Simulation Output of Hit Generator TB:" << std::endl
               << "*******************************************" << std::endl;

    return;
}

// *****************************************************************************
hit_generator_tb::~hit_generator_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void hit_generator_tb::check_output()
{
    while(1)
    {
        wait();

        for (auto& hit_signal: hit_signals)
        {
            stub read_stub(configuration.output_stub_mpa);
            while (hit_signal.nb_read(read_stub))
            {
                std::pair<bool, sc_map_list_key<chip_address> > signal_key;
                signal_key = hit_signals.get_key(hit_signal);
                chip_address chp_address = signal_key.second.value;
                log_buffer << sc_time_stamp () << std::dec
                           << " @ hit_generator." << chp_address;

                if (read_stub.configuration.pixel_bits > 1)
                {
                    log_buffer << " (PS): "
                               << read_stub.get_strip() << ","
                               << read_stub.get_pixel() << " - "
                               << read_stub.get_bend() << std::endl;
                }
                else
                {
                    log_buffer << " (2S): " << std::hex
                               << read_stub.get_strip() << " - "
                               << read_stub.get_bend() << std::endl;
                }
            }
        }
    }

}

// *****************************************************************************
void hit_generator_tb::check_hit_counter()
{
    while(1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": hit_counter = "
                   << hit_cnt_signal.read() << std::endl;
    }

}
