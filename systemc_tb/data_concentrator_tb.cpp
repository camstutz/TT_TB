/*!
 * @file data_concentrator_tb.cpp
 * @author Christian Amstutz
 * @date Mar 27, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

data_concentrator_tb::data_concentrator_tb(sc_module_name _name) :
        sc_module(_name),
        rst("rst"),
        fe_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP, "fe_signal"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_concentrator("Data_Concentrator_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_data_concentrator.clk(LHC_clock);
    dut_data_concentrator.rst(rst);
    dut_data_concentrator.fe_stub_in.bind(fe_signals);
    dut_data_concentrator.dc_out(dc_output);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_hit_data);
    SC_THREAD(print_output);
        sensitive << dc_output;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of Data Concentrator TB:" << std::endl
            << "*******************************************" << std::endl;

    return;
}

// *****************************************************************************
void data_concentrator_tb::end_of_elaboration()
{
    for (auto& fe_signal : fe_signals)
    {
        fe_signal.write(fe_out_data());
    }

    return;
}

// *****************************************************************************
data_concentrator_tb::~data_concentrator_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void data_concentrator_tb::generate_hit_data()
{
    wait(50, SC_NS);
    write_fe(0,0,255,0);

    wait(25,SC_NS);
    release_fe(0,0);

    wait(200, SC_NS);
    write_fe(0,0,255,31);
    write_fe(1,1,255,31);
    write_fe(1,2,255,31);
    write_fe(1,0,255,31);
    write_fe(2,1,255,31);
    write_fe(2,2,255,31);
    write_fe(2,0,255,31);
    write_fe(3,1,255,31);
    write_fe(3,2,255,31);
    write_fe(3,0,255,31);
    write_fe(4,1,255,31);
    write_fe(4,2,255,31);
    write_fe(4,0,255,31);

    wait(25,SC_NS);
    release_fe(0,0);
    release_fe(1,1);
    release_fe(1,2);
    release_fe(1,0);
    release_fe(2,1);
    release_fe(2,2);
    release_fe(2,0);
    release_fe(3,1);
    release_fe(3,2);
    release_fe(3,0);
    release_fe(4,1);
    release_fe(4,2);
    release_fe(4,0);

    return;
}

// *****************************************************************************
void data_concentrator_tb::print_output()
{
    while(1)
    {
         wait();
         log_buffer << sc_time_stamp() << ": " << dc_output.read() << std::endl;
    }
}

// *****************************************************************************
void data_concentrator_tb::write_fe( const unsigned int fe_chip,
        const unsigned int hit_nr, const unsigned int address,
        const unsigned int bend)
{
    fe_out_data fe_data;
    fe_data.set_dv(true);
    auto stub = fe_out_data::fe_stub_t(address, bend);
    fe_data.set_data(stub);
    fe_signals.at(fe_chip, hit_nr).write(fe_data);

    unsigned int output = stub.get_bit_vector().to_uint();
    log_buffer << sc_time_stamp() << ": writing to "
               << fe_signals.at(fe_chip,hit_nr).name()
               << " --> " << std::hex << output << std::dec
               << std::endl;

    return;
}

// *****************************************************************************
void data_concentrator_tb::release_fe(const unsigned int fe_chip,
        const unsigned int hit_nr)
{
    fe_signals.at(fe_chip, hit_nr).write(fe_out_data());

    return;
}
