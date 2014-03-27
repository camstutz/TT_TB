/*!
 * @file front_end_chip_tb.cpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "front_end_chip_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

front_end_chip_tb::front_end_chip_tb(sc_module_name _name) :
        sc_module(_name),
        en_sig("en"),
        stub_input_sig("stub_input"),
        fe_out_signals(MAX_HITS_PER_FE_CHIP, "fe_out_sig"),
        LHC_clock("LHC_clock", 25, SC_NS, 0.5, 10, SC_NS, true),
        dut_front_end_chip("Front_End_Chip_DUT") {

    // ----- Creation and binding of signals -----------------------------------
    dut_front_end_chip.clk(LHC_clock);
    dut_front_end_chip.en(en_sig);
    dut_front_end_chip.stub_input(stub_input_sig);
    dut_front_end_chip.hit_outputs.bind(fe_out_signals);

    // ----- Process registration ----------------------------------------------

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
               << "Simulation Output of Front End Chip TB:" << std::endl
               << "*******************************************" << std::endl;
    return;
}

// *****************************************************************************
void front_end_chip_tb::end_of_elaboration()
{
    SC_THREAD(generate_stubs);
    SC_THREAD(analyse_FE_out);
    for (auto& fe_out_sig : fe_out_signals)
    {
      sensitive << fe_out_sig;
    }
    return;
}

// *****************************************************************************
front_end_chip_tb::~front_end_chip_tb()
{
  std::cout << log_buffer.str();

  return;
}

// *****************************************************************************
void front_end_chip_tb::generate_stubs()
{
    fe_out_data::fe_stub_t stim_stub;

    wait(60, SC_NS);
    en_sig.write(1);
    stim_stub.set_strip(255);
    stim_stub.set_bend(1);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(32, SC_NS);
    stim_stub.set_strip(100);
    stim_stub.set_bend(2);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    stim_stub.set_strip(120);
    stim_stub.set_bend(3);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(1, SC_NS);
    stim_stub.set_strip(101);
    stim_stub.set_bend(4);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    wait(1, SC_NS);
    stim_stub.set_strip(101);
    stim_stub.set_bend(5);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(25, SC_NS);
    stim_stub.set_strip(1);
    stim_stub.set_bend(6);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    wait(25, SC_NS);
    stim_stub.set_strip(12);
    stim_stub.set_bend(7);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    stim_stub.set_strip(13);
    stim_stub.set_bend(8);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    //! todo: there is an error here with this event falling on a clock edge and does not show on the output
    wait(16, SC_NS);
    stim_stub.set_strip(14);
    stim_stub.set_bend(9);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;
    wait(1, SC_NS);
    stim_stub.set_strip(1);
    stim_stub.set_bend(1);
    stub_input_sig.write(stim_stub);
    log_buffer << sc_time_stamp() << ": TX - " << stim_stub << std::endl;

    return;
}

// *****************************************************************************
void front_end_chip_tb::analyse_FE_out()
{
    while(1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": DV ";
        for (auto& fe_out_signal : fe_out_signals)
        {
            log_buffer << fe_out_signal.read().get_dv();
            log_buffer << "-";
        }
        log_buffer << std::endl;

        for (auto& fe_out_signal : fe_out_signals)
        {
            fe_out_data read_hit = fe_out_signal.read();
            if(fe_out_signal.read().get_dv() == true)
            {
                std::pair<bool, sc_map_linear<sc_signal<fe_out_data>>::full_key_type> signal_key;
                signal_key = fe_out_signals.get_key(fe_out_signal);
                auto act_stub = read_hit.get_data();
                log_buffer << sc_time_stamp() <<" Hit" << signal_key.second.X_dim << ": "
                           << std::hex
                           << " Address: 0x" << act_stub.get_strip()
                           << " Bend: 0x" << act_stub.get_bend()
                           << std::dec << std::endl;
            }
        }
    }

}
