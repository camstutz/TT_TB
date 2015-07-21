/*!
 * @file hit_generator_tb.cpp
 * @author Christian Amstutz
 * @date June 18, 2015
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

hit_generator_tb::hit_generator_tb(sc_module_name _name) :
        sc_module(_name),
        hit_signals_mpa(NR_DETECTOR_MPA_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z,
                NR_FE_CHIP_PER_MODULE, "hit_signal_mpa", 0, 0, 0, 0),
        hit_signals_cbc(NR_DETECTOR_CBC_LAYERS, NR_DETECTOR_PHI, NR_DETECTOR_Z,
                NR_FE_CHIP_PER_MODULE, "hit_signal_cbc", NR_DETECTOR_MPA_LAYERS, 0,
                0, 0),
        hit_cnt_signal("hit_cnt_signal"),
        dut_hit_generator("Hit_Generator_DUT", "/home/amstutz/eclipse/git/TT_TB/source/systemc/module_tests/test_hits.txt")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_hit_generator.mpa_stub_outputs.bind(hit_signals_mpa);
    dut_hit_generator.cbc_stub_outputs.bind(hit_signals_cbc);
    dut_hit_generator.hit_cnt.bind(hit_cnt_signal);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(check_output);
    for (auto& hit_signal : hit_signals_mpa)
    {
        sensitive << hit_signal.data_written_event();
    }
    for (auto& hit_signal : hit_signals_cbc)
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

        for (auto& hit_signal: hit_signals_mpa)
        {
            hit_generator::mpa_stub_t read_stub;
            while (hit_signal.nb_read(read_stub))
            {
                std::pair<bool, sc_map_4d<sc_fifo<hit_generator::mpa_stub_t>>::key_type> signal_key;
                signal_key = hit_signals_mpa.get_key(hit_signal);
                log_buffer << sc_time_stamp () << " @ hit_generator."
                           << "L" << signal_key.second.W
                           << "Phi" << signal_key.second.Z
                           << "Z" << signal_key.second.Y
                           << "FE" << signal_key.second.X
                           << " (MPA): " << std::hex
                           << read_stub.get_bx() << " - "
                           << "0x" << read_stub.get_strip() << ","
                           << "0x" << read_stub.get_pixel() << " - "
                           << "0x" << read_stub.get_bend() << std::endl;
            }
        }

        for (auto& hit_signal: hit_signals_cbc)
        {
            hit_generator::cbc_stub_t read_stub;
            while (hit_signal.nb_read(read_stub))
            {
                std::pair<bool, sc_map_4d<sc_fifo<hit_generator::cbc_stub_t>>::key_type> signal_key;
                signal_key = hit_signals_cbc.get_key(hit_signal);
                log_buffer << sc_time_stamp () << " @ hit_generator."
                           << "L" << signal_key.second.W
                           << "Phi" << signal_key.second.Z
                           << "Z" << signal_key.second.Y
                           << "FE" << signal_key.second.X
                           << " (CBC): " << std::hex
                           << "0x" << read_stub.get_strip() << " - "
                           << "0x" << read_stub.get_bend() << std::endl;
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
