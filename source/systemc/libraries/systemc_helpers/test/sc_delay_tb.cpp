/*!
 * @file sc_delay_tb.cpp
 * @author Christian Amstutz
 * @date Apr 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "sc_delay_tb.hpp"

//******************************************************************************
sc_delay_tb::sc_delay_tb(sc_module_name _name) :
        sc_module(_name),
        delay_element("delay_element"),
        in_signal("in_signal"),
        out_signal("out_signal"),
        clock("clock", 10, SC_NS, 0.5, 30, SC_NS, true)
{
    SC_THREAD(create_signal);
    SC_THREAD(detect_signal);
        sensitive << out_signal;

    delay_element.clk(clock);
    delay_element.input(in_signal);
    delay_element.delayed(out_signal);

    log_buffer << std::endl;
    log_buffer << "*******************************************" << std::endl;
    log_buffer << "Simulation Output of sc_delay TB:" << std::endl;
    log_buffer << "*******************************************" << std::endl;


    return;
}

// *****************************************************************************
sc_delay_tb::~sc_delay_tb()
{
    std::cout << log_buffer.str();

    return;
}

// *****************************************************************************
void sc_delay_tb::create_signal()
{

    wait(40, SC_NS);
    in_signal.write(1);
    log_buffer << sc_time_stamp() << ": input = 1" << std::endl;

    wait(10, SC_NS);
    in_signal.write(2);
    log_buffer << sc_time_stamp() << ": input = 2" << std::endl;

    wait(15, SC_NS);
    in_signal.write(3);
    log_buffer << sc_time_stamp() << ": input = 3" << std::endl;

    wait(55, SC_NS);
    in_signal.write(4);
    log_buffer << sc_time_stamp() << ": input = 4" << std::endl;

    wait(10, SC_NS);
    in_signal.write(5);
    log_buffer << sc_time_stamp() << ": input = 5" << std::endl;

    wait(2, SC_NS);
    in_signal.write(6);
    log_buffer << sc_time_stamp() << ": input = 6" << std::endl;

    return;
}

// *****************************************************************************
void sc_delay_tb::detect_signal()
{
    while (1)
    {
        wait();

        log_buffer << sc_time_stamp() << ": output = " <<
                delay_element.delayed.read() << std::endl;
    }

    return;
}
