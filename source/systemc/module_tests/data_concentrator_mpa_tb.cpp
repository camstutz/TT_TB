/*!
 * @file data_concentrator_mpa_tb.cpp
 * @author Christian Amstutz
 * @date June 29, 2015
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "data_concentrator_mpa_tb.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class front_end_chip_tb
 * The module is sensitive to ...
 */

data_concentrator_mpa_tb::data_concentrator_mpa_tb(sc_module_name _name,
        track_trigger_config configuration) :
        sc_module(_name),
        rst("rst"),
        data_valid(configuration.mpa_sensor_module.fe_chip_per_side, configuration.mpa_sensor_module.frontend_chip.max_stubs_per_cycle, "data_valid"),
        fe_signals(configuration.mpa_sensor_module.fe_chip_per_side, configuration.mpa_sensor_module.frontend_chip.max_stubs_per_cycle, "fe_signal"),
        LHC_clock("LHC_clock", configuration.LHC_clock_period, SC_NS, 0.5, 25, SC_NS, true),
        dut_data_concentrator("Data_Concentrator_MPA_DUT",
                configuration.mpa_data_concentrator),
        dut_configuration(configuration.mpa_data_concentrator)
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
            << "Simulation Output of Data Concentrator MPA TB:" << std::endl
            << "**********************************************" << std::endl;

    return;
}

// *****************************************************************************
data_concentrator_mpa_tb::~data_concentrator_mpa_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void data_concentrator_mpa_tb::generate_hit_data()
{
    data_valid.write(false);
    fe_signals.write(data_concentrator::fe_stub_t());

    wait(50, SC_NS);
    write_fe(2,0,1,3,255,4);

    wait(25,SC_NS);
    release_fe(2,0);

    wait(200, SC_NS);
    write_fe(0,0,0,0,255,31);
    write_fe(1,1,0,0,255,31);
    write_fe(6,0,0,0,255,31);
    write_fe(1,0,0,0,255,31);
    write_fe(2,1,0,0,255,31);
    write_fe(6,1,0,0,255,31);
    write_fe(2,0,0,0,255,31);
    write_fe(3,1,0,0,255,31);
    write_fe(5,0,0,0,255,31);
    write_fe(3,0,0,0,255,31);
    write_fe(4,1,0,0,255,31);
    write_fe(5,1,0,0,255,31);
    write_fe(4,0,0,0,255,31);

    wait(25,SC_NS);
    release_fe(0,0);
    release_fe(1,1);
    release_fe(6,0);
    release_fe(1,0);
    release_fe(2,1);
    release_fe(6,1);
    release_fe(2,0);
    release_fe(3,1);
    release_fe(5,0);
    release_fe(3,0);
    release_fe(4,1);
    release_fe(5,1);
    release_fe(4,0);

    return;
}

// *****************************************************************************
void data_concentrator_mpa_tb::print_output()
{
    while(1)
    {
         wait();
         log_buffer << sc_time_stamp() << ": " << dc_output.read() << std::endl;
    }
}

// *****************************************************************************
void data_concentrator_mpa_tb::write_fe(const unsigned int fe_chip,
		const unsigned int hit_nr, const unsigned int bx,
		const unsigned int pixel, const unsigned int strip,
		const unsigned int bend)
{
    data_concentrator::fe_stub_t fe_data(
            dut_configuration.frontend_chip_type.output_stub, 0, bx, 0, strip,
            bend, pixel);

    data_valid.at(fe_chip, hit_nr).write(true);
    fe_signals.at(fe_chip, hit_nr).write(fe_data);

    log_buffer << sc_time_stamp() << ": writing to "
               << fe_signals.at(fe_chip,hit_nr).name()
               << " --> " << fe_data << std::dec
               << std::endl;

    return;
}

// *****************************************************************************
void data_concentrator_mpa_tb::release_fe(const unsigned int fe_chip,
        const unsigned int hit_nr)
{
    data_valid.at(fe_chip, hit_nr).write(false);
	fe_signals.at(fe_chip, hit_nr).write(data_concentrator::fe_stub_t(dut_configuration.frontend_chip_type.output_stub));

    return;
}
