/*!
 * @file frontend_chip_cbc_tb.cpp
 * @author Christian Amstutz
 * @date December 19, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "frontend_chip_cbc_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

frontend_chip_cbc_tb::frontend_chip_cbc_tb(sc_module_name _name,
		sc_trace_file* trace_file, track_trigger_config configuration) :
		sc_module(_name),
        stub_input_sig("stub_input"),
        data_valid_signals(MAX_HITS_PER_CBC_FE_CHIP, "data_valid_sig"),
        fe_out_signals(MAX_HITS_PER_CBC_FE_CHIP, "fe_out_sig"),
        LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true),
        dut_front_end_chip("Front_End_Chip_DUT", configuration.cbc_front_end_chip)
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
               << "Simulation Output of Front End Chip CBC TB:" << std::endl
               << "*******************************************" << std::endl;

    trace(trace_file);

    SC_THREAD(generate_stubs);
    SC_THREAD(analyse_FE_out);
        sensitive << data_valid_signals;
        sensitive << fe_out_signals;

    return;
}

// *****************************************************************************
frontend_chip_cbc_tb::~frontend_chip_cbc_tb()
{
  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void frontend_chip_cbc_tb::generate_stubs()
{
    frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t>::input_stub_t stim_stub;

    // at 60 ns
    wait(60, SC_NS);
    write_stub(0xFF, 0x1);

    // at 92 ns
    wait(32, SC_NS);
    write_stub(0x80, 0x2);
    write_stub(0x85, 0x3);

    // at 93 ns
    wait(1, SC_NS);
    write_stub(0x81, 0x4);

    // at 94 ns
    wait(1, SC_NS);
    write_stub(0x82, 0x5);

    // at 119 ns
    wait(25, SC_NS);
    write_stub(0x1, 0x6);

    // at 144 ns
    wait(25, SC_NS);
    write_stub(0x12, 0x7);
    write_stub(0x13, 0x8);

    //! todo: there is an error here with this event falling on a clock edge and does not show on the output
    // at 160 ns
    wait(16, SC_NS);
    write_stub(0xD, 0x9);

    // at 161 ns
    wait(1, SC_NS);
    write_stub(0x1, 0x1);

    // at 201 ns
    wait(40, SC_NS);
    write_stub(0x14, 0x9);

    // at 202 ns
    wait(1, SC_NS);
    write_stub(0x1, 0x1);

    return;
}

// *****************************************************************************
void frontend_chip_cbc_tb::analyse_FE_out()
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
            frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t>::output_stub_t read_stub = fe_out_signal.read();
            std::pair<bool, sc_map_linear<sc_signal<frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t>::output_stub_t>>::full_key_type> signal_key;
            signal_key = fe_out_signals.get_key(fe_out_signal);

            if(data_valid_signals.at(signal_key.second.X_dim).read())
            {
                log_buffer << sc_time_stamp() <<" Stub" << signal_key.second.X_dim << ": "
                           << std::hex
                           << " Strip: 0x" << read_stub.get_strip()
                           << " Bend: 0x" << read_stub.get_bend()
                           << std::dec << std::endl;
            }
        }
    }

}

// *****************************************************************************
void frontend_chip_cbc_tb::trace(sc_trace_file* trace_file)
{
	sc_trace(trace_file, LHC_clock, "CBC.clock");
	sc_trace(trace_file, data_valid_signals.at(0), "CBC.data_valid_0");
	sc_trace(trace_file, data_valid_signals[1], "CBC.data_valid_1");
	sc_trace(trace_file, data_valid_signals[2], "CBC.data_valid_2");
	sc_trace(trace_file, fe_out_signals[0], "CBC.fe_out_sig_0");
	sc_trace(trace_file, fe_out_signals[1], "CBC.fe_out_sig_1");
	sc_trace(trace_file, fe_out_signals[2], "CBC.fe_out_sig_2");

	return;
}

// *****************************************************************************
void frontend_chip_cbc_tb::write_stub(frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t>::input_stub_t::strip_t strip,
        frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t>::input_stub_t::bend_t bend)
{
    frontend_chip<fe_cbc_stub_t, fe_cbc_stub_t>::input_stub_t stim_stub(0x00, strip, bend);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    return;
}
