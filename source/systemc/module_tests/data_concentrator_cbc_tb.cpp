/*!
 * @file data_concentrator_cbc_tb.cpp
 * @author Christian Amstutz
 * @date July 7, 2014
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator_cbc_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

data_concentrator_cbc_tb::data_concentrator_cbc_tb(sc_module_name _name) :
        sc_module(_name),
        data_valid(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_CBC_FE_CHIP, "data_valid"),
        fe_signals(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_CBC_FE_CHIP, "fe_signal"),
        LHC_clock("LHC_clock", LHC_CLOCK_PERIOD_NS, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_concentrator("Data_Concentrator_CBC_DUT")
{
    // ----- Creation and binding of signals -----------------------------------
    dut_data_concentrator.clk.bind(LHC_clock);
    dut_data_concentrator.data_valid.bind(data_valid);
    dut_data_concentrator.fe_stub_in.bind(fe_signals);
    dut_data_concentrator.dc_out.bind(dc_output);

    // ----- Process registration ----------------------------------------------
    SC_THREAD(generate_hit_data);
    SC_THREAD(print_output);
        sensitive << dc_output;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    log_buffer << std::endl
            << "Simulation Output of Data Concentrator CBC TB:" << std::endl
            << "**********************************************" << std::endl;

    return;
}

// *****************************************************************************
data_concentrator_cbc_tb::~data_concentrator_cbc_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void data_concentrator_cbc_tb::generate_hit_data()
{
    data_valid.write_all(false);
    fe_signals.write_all(data_concentrator_cbc::in_stub_t());

    wait(25, SC_NS);
    write_fe(0,0,255,0);

    wait(25,SC_NS);
    release_fe(0,0);

    wait(400, SC_NS);
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
void data_concentrator_cbc_tb::print_output()
{
    while(1)
    {
         wait();
         log_buffer << sc_time_stamp() << ": " << dc_output.read() << std::endl;
    }
}

// *****************************************************************************
void data_concentrator_cbc_tb::write_fe( const unsigned int fe_chip,
        const unsigned int hit_nr, const unsigned int address,
        const unsigned int bend)
{
    data_concentrator_cbc::in_stub_t fe_data(address, bend);

    data_valid.at(fe_chip, hit_nr).write(true);
    fe_signals.at(fe_chip, hit_nr).write(fe_data);

    unsigned int output = fe_data.get_bitvector().to_uint();
    log_buffer << sc_time_stamp() << ": writing to "
               << fe_signals.at(fe_chip,hit_nr).name()
               << " --> " << std::hex << output << std::dec
               << std::endl;

    return;
}

// *****************************************************************************
void data_concentrator_cbc_tb::release_fe(const unsigned int fe_chip,
        const unsigned int hit_nr)
{
    data_valid.at(fe_chip, hit_nr).write(false);
	fe_signals.at(fe_chip, hit_nr).write(data_concentrator_cbc::in_stub_t());

    return;
}
