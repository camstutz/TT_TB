/*!
 * @file frontend_chip_mpa_tb.cpp
 * @author Christian Amstutz
 * @date July 7, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "frontend_chip_mpa_tb.hpp"

// *****************************************************************************

// *****************************************************************************

frontend_chip_mpa_tb::frontend_chip_mpa_tb(sc_module_name _name,
		sc_trace_file* trace_file) :
        sc_module(_name),
        en_sig("en"),
        stub_input_sig("stub_input"),
        data_valid_signals(MAX_HITS_PER_MPA_FE_CHIP, "data_valid_sig"),
        fe_out_signals(MAX_HITS_PER_MPA_FE_CHIP, "fe_out_sig"),
        LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true),
        dut_front_end_chip("Front_End_Chip_DUT") {

    // ----- Creation and binding of signals -----------------------------------
    dut_front_end_chip.clk.bind(LHC_clock);
    dut_front_end_chip.en.bind(en_sig);
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

    return;
}

// *****************************************************************************
void frontend_chip_mpa_tb::end_of_elaboration()
{
    SC_THREAD(generate_stubs);
    SC_THREAD(analyse_FE_out);
    for (auto& dv_sig : data_valid_signals)
    {
      sensitive << dv_sig;
    }

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
    frontend_chip_mpa::fe_mpa_stub_t stim_stub;

    wait(60, SC_NS);
    en_sig.write(1);
    stim_stub.set_bx(0);
    stim_stub.set_pixel(7);
    stim_stub.set_strip(255);
    stim_stub.set_bend(1);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(32, SC_NS);
    stim_stub.set_bx(0);
    stim_stub.set_pixel(8);
    stim_stub.set_strip(100);
    stim_stub.set_bend(2);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    stim_stub.set_bx(0);
    stim_stub.set_pixel(9);
    stim_stub.set_strip(120);
    stim_stub.set_bend(3);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(1, SC_NS);
    stim_stub.set_bx(1);
    stim_stub.set_pixel(10);
    stim_stub.set_strip(101);
    stim_stub.set_bend(4);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    wait(1, SC_NS);
    stim_stub.set_bx(1);
    stim_stub.set_pixel(11);
    stim_stub.set_strip(101);
    stim_stub.set_bend(5);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(25, SC_NS);
    stim_stub.set_pixel(12);
    stim_stub.set_strip(1);
    stim_stub.set_bend(6);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(25, SC_NS);
    stim_stub.set_bx(0);
    stim_stub.set_pixel(13);
    stim_stub.set_strip(12);
    stim_stub.set_bend(7);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    stim_stub.set_bx(0);
    stim_stub.set_pixel(14);
    stim_stub.set_strip(13);
    stim_stub.set_bend(8);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    //! todo: there is an error here with this event falling on a clock edge and does not show on the output
    wait(16, SC_NS);
    stim_stub.set_bx(1);
    stim_stub.set_pixel(14);
    stim_stub.set_strip(14);
    stim_stub.set_bend(9);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    wait(1, SC_NS);
    stim_stub.set_bx(0);
    stim_stub.set_pixel(15);
    stim_stub.set_strip(1);
    stim_stub.set_bend(1);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(40, SC_NS);
    stim_stub.set_bx(1);
    stim_stub.set_pixel(16);
    stim_stub.set_strip(14);
    stim_stub.set_bend(9);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    wait(1, SC_NS);
    stim_stub.set_bx(1);
    stim_stub.set_pixel(17);
    stim_stub.set_strip(1);
    stim_stub.set_bend(1);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

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
            frontend_chip_mpa::fe_mpa_stub_t read_stub = fe_out_signal.read();
            std::pair<bool, sc_map_linear<sc_signal<frontend_chip_mpa::fe_mpa_stub_t>>::full_key_type> signal_key;
            signal_key = fe_out_signals.get_key(fe_out_signal);

            if(data_valid_signals.at(signal_key.second.X_dim).read())
            {
                log_buffer << sc_time_stamp() <<" Stub" << signal_key.second.X_dim << ": "
                           << std::hex
                           << " BX: 0x" << read_stub.get_bx()
                           << " Pixel: 0x" << read_stub.get_pixel()
                           << " Strip: 0x" << read_stub.get_strip()
                           << " Bend: 0x" << read_stub.get_bend()
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
