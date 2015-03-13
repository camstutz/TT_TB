/*!
 * @file frontend_chip_mpa_tb.cpp
 * @author Christian Amstutz
 * @date March 13, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "frontend_chip_mpa_tb.hpp"

// *****************************************************************************

// *****************************************************************************

frontend_chip_mpa_tb::frontend_chip_mpa_tb(sc_module_name _name,
		sc_trace_file* trace_file) :
        sc_module(_name),
        LHC_cycle("LHC_cycle"),
        stub_input_sig("stub_input"),
        data_valid_signals(MAX_HITS_PER_MPA_FE_CHIP, "data_valid_sig"),
        fe_out_signals(MAX_HITS_PER_MPA_FE_CHIP, "fe_out_sig"),
        LHC_clock("LHC_clock", 25, SC_NS, 0.5, 0, SC_NS, true),
        LHC_cycle_cnt("LHC_cycle_cnt"),
        dut_front_end_chip("Front_End_Chip_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    LHC_cycle_cnt.LHC_clock.bind(LHC_clock);
    LHC_cycle_cnt.LHC_cycle.bind(LHC_cycle);

    dut_front_end_chip.LHC_cycle.bind(LHC_cycle);
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
        data_valid_signals.make_sensitive(sensitive);
        fe_out_signals.make_sensitive(sensitive);


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
    frontend_chip_mpa::input_stub_t stim_stub;

    wait(LHC_cycle.value_changed_event());
    wait(LHC_cycle.value_changed_event());
    wait(LHC_cycle.value_changed_event());
    write_stub(0x0, 0x7, 0xFF, 0x1);

    wait(LHC_cycle.value_changed_event());
    write_stub(0x0, 0x7, 0xFF, 0x2);

    wait(LHC_cycle.value_changed_event());
    write_stub(0x0, 0x7, 0xFF, 0x3);

    wait(LHC_cycle.value_changed_event());
    write_stub(0x0, 0x7, 0xFF, 0x4);

    wait(LHC_cycle.value_changed_event());
    //write_stub(0x0, 0x7, 0xFF, 0x5);

    wait(LHC_cycle.value_changed_event());
    write_stub(0x0, 0x7, 0xFF, 0x6);

    wait(LHC_cycle.value_changed_event());
    write_stub(0x0, 0x7, 0xFF, 0x7);

//    wait(LHC_cycle.value_changed_event());
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x0, 0x8, 0x80, 0x2);
//    write_stub(0x0, 0x9, 0x90, 0x3);
//    write_stub(0x0, 0x9, 0x91, 0x3);
//    write_stub(0x0, 0x9, 0x92, 0x3);
//
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x0, 0xA, 0x81, 0x4);
//    write_stub(0x0, 0xB, 0x82, 0x5);
//    write_stub(0x0, 0xB, 0x42, 0x6);
//
//    // at 119 ns
//    wait(LHC_cycle.value_changed_event());
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x0, 0xC, 0x1, 0x6);
//
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x0, 0xD, 0x12, 0x7);
//    write_stub(0x0, 0xE, 0x15, 0x8);
//
//    // at 160 ns
//    wait(LHC_cycle.value_changed_event());
//    wait(LHC_cycle.value_changed_event());
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x1, 0x14, 0x14, 0x9);
//
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x0, 0xF, 0x1, 0xA);
//
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x1, 0x10, 0xB, 0xB);
//
//    wait(LHC_cycle.value_changed_event());
//    wait(LHC_cycle.value_changed_event());
//    write_stub(0x1, 0x12, 0x1, 0xC);

    wait(50, SC_NS);

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
            frontend_chip_mpa::output_stub_t read_stub = fe_out_signal.read();
            std::pair<bool, sc_map_linear<sc_signal<frontend_chip_mpa::output_stub_t>>::full_key_type> signal_key;
            signal_key = fe_out_signals.get_key(fe_out_signal);

            if(data_valid_signals.at(signal_key.second.X_dim).read())
            {
                log_buffer << sc_time_stamp() <<" Stub" << signal_key.second.X_dim << ": "
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
void frontend_chip_mpa_tb::write_stub(frontend_chip_mpa::input_stub_t::bx_t bx,
        frontend_chip_mpa::input_stub_t::pixel_t pixel,
        frontend_chip_mpa::input_stub_t::strip_t strip,
        frontend_chip_mpa::input_stub_t::bend_t bend)
{
    frontend_chip_mpa::input_stub_t stim_stub(bx, pixel, strip, bend);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    return;
}
