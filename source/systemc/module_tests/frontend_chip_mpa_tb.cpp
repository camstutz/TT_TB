/*!
 * @file frontend_chip_mpa_tb.cpp
 * @author Christian Amstutz
 * @date August 28, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "frontend_chip_mpa_tb.hpp"

// *****************************************************************************

// *****************************************************************************

frontend_chip_mpa_tb::frontend_chip_mpa_tb(sc_module_name _name,
		sc_trace_file* trace_file, track_trigger_config configuration) :
        sc_module(_name),
        en_sig("en"),
        stub_input_sig("stub_input"),
        data_valid_signals(configuration.mpa_sensor_module.frontend_chip.max_stubs_per_cycle, "data_valid_sig"),
        fe_out_signals(configuration.mpa_sensor_module.frontend_chip.max_stubs_per_cycle, "fe_out_sig"),
        LHC_clock("LHC_clock", 25, SC_NS, 0.5, 50, SC_NS, true),
        dut_front_end_chip("Front_End_Chip_DUT", configuration.mpa_sensor_module.frontend_chip)
{
    // ----- Creation and binding of signals -----------------------------------
    dut_front_end_chip.clk.bind(LHC_clock);
    dut_front_end_chip.stub_input.bind(stub_input_sig);
    dut_front_end_chip.data_valid.bind(data_valid_signals);
    dut_front_end_chip.stub_outputs.bind(fe_out_signals);

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
               << "Simulation Output of Front End Chip MPA TB:" << std::endl
               << "*******************************************" << std::endl;

    trace(trace_file);

    SC_THREAD(generate_stubs);
    SC_THREAD(analyse_FE_out);
        sensitive << data_valid_signals;
        sensitive << fe_out_signals;


    return;
}

// *****************************************************************************
frontend_chip_mpa_tb::~frontend_chip_mpa_tb()
{
  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void frontend_chip_mpa_tb::generate_stubs()
{
    // at 60 ns
    wait(85, SC_NS);
    en_sig.write(1);
    write_stub(0x0, 0x7, 0x01, 0x1);

    // at 92 ns
    wait(32, SC_NS);
    write_stub(0x0, 0x8, 0x01, 0x2);
    write_stub(0x0, 0x9, 0x01, 0x3);
    write_stub(0x0, 0x9, 0x02, 0x3);
    write_stub(0x0, 0x9, 0x03, 0x3);

    // at 93 ns
    wait(1, SC_NS);
    write_stub(0x0, 0xA, 0x01, 0x4);

    wait(25, SC_NS);
    write_stub(0x0, 0xB, 0x01, 0x5);
    write_stub(0x0, 0xB, 0x01, 0x6);

    wait(25, SC_NS);
    write_stub(0x0, 0xC, 0x02, 0x6);

    wait(25, SC_NS);
    write_stub(0x0, 0xD, 0x01, 0x7);
    write_stub(0x0, 0xE, 0x01, 0x8);

    // at 160 ns
    wait(16, SC_NS);
    write_stub(0x1, 0x14, 0x01, 0x9);

    // at 161 ns
    wait(1, SC_NS);
    write_stub(0x0, 0xF, 0x01, 0xA);

    // at 200 ns
    wait(19, SC_NS);
    write_stub(0x1, 0x10, 0x01, 0xB);

    // at 201 ns
    wait(1, SC_NS);
    write_stub(0x1, 0x12, 0x01, 0xC);

    return;
}

// *****************************************************************************
void frontend_chip_mpa_tb::analyse_FE_out()
{
    while(1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": DV ";
        for (auto& dv_signal : data_valid_signals)
        {
            log_buffer << dv_signal.read();
            log_buffer << "-";
        }
        log_buffer << std::endl;

        for (auto& fe_out_signal : fe_out_signals)
        {
            frontend_chip::output_stub_t read_stub = fe_out_signal.read();
            std::pair<bool, sc_map_linear<sc_signal<frontend_chip::output_stub_t>>::key_type> signal_key;
            signal_key = fe_out_signals.get_key(fe_out_signal);

            if(data_valid_signals.at(signal_key.second.X).read())
            {
                log_buffer << sc_time_stamp() <<" Stub" << signal_key.second.X << ": "
                           << std::hex
                           << " BX:0x" << read_stub.get_bx()
                           << " Pixel:0x" << read_stub.get_pixel()
                           << " Strip:0x" << read_stub.get_strip()
                           << " Bend:0x" << read_stub.get_bend()
                           << std::dec << std::endl;
            }
        }
    }

}

// *****************************************************************************
void frontend_chip_mpa_tb::trace(sc_trace_file* trace_file)
{
    sc_trace(trace_file, LHC_clock, "MPA.clock");
    sc_trace(trace_file, data_valid_signals.at(0), "MPA.data_valid_0");
    sc_trace(trace_file, data_valid_signals[1], "MPA.data_valid_1");
    sc_trace(trace_file, fe_out_signals[0], "MPA.fe_out_sig_0");
    sc_trace(trace_file, fe_out_signals[1], "MPA.fe_out_sig_1");

	return;
}

// *****************************************************************************
void frontend_chip_mpa_tb::write_stub(unsigned int bx, unsigned int pixel,
        unsigned int strip, int bend)
{
    frontend_chip::input_stub_t stim_stub(dut_front_end_chip.input_stub_config,
            0, bx, 0, strip, bend, pixel );
    stub_input_sig.write(stim_stub);

    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    return;
}
