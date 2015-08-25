/*!
 * @file sc_delay_signal.hpp
 * @author Christian Amstutz
 * @date August 19, 2015
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#pragma once

#include <vector>

#include <systemc.h>

/*!
 * @brief
 */
template <typename signal_t>
class sc_delay_signal : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_in<signal_t> input;
    sc_out<signal_t> delayed;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<unsigned int> read_ptr;
    sc_signal<unsigned int> write_ptr;

    std::vector<bool> data_valid_buffer;
    std::vector<signal_t> value_buffer;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_output();
    void zero_delay();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    sc_delay_signal(sc_module_name _name, unsigned int delay_cycles);
    SC_HAS_PROCESS(sc_delay_signal);

private:
    const unsigned int delay_cycles;

    void increase_ptr(sc_signal<unsigned int>& ptr);
};

//******************************************************************************

//******************************************************************************
/*!
 * @class sc_delay_signal
 *
 * The module is sensitive to ....
 */
template <typename signal_t>
sc_delay_signal<signal_t>::sc_delay_signal(sc_module_name _name,
        unsigned int delay_cycles) :
        sc_module(_name),
        clk("clk"),
        input("input"),
        delayed("delayed"),
        read_ptr("read_ptr"),
        write_ptr("write_ptr"),
        delay_cycles(delay_cycles)
{
    // ----- Process registration ----------------------------------------------
    if (delay_cycles == 0)
    {
        SC_THREAD(zero_delay);
            sensitive << input;
    }
    else
    {
        SC_THREAD(read_input);
            sensitive << input << clk.pos();
        SC_THREAD(write_output);
            sensitive << clk.pos();
    }

    // ----- Module variable initialization ------------------------------------
    data_valid_buffer.resize(delay_cycles, false);
    value_buffer.resize(delay_cycles, signal_t());

    write_ptr.write(0);
    if (delay_cycles > 1)
    {
        read_ptr.write(1);
    }
    else
    {
        read_ptr.write(0);
    }

    // ----- Module instance / channel binding ---------------------------------

    return;
}

//******************************************************************************
template <typename signal_t>
void sc_delay_signal<signal_t>::read_input()
{
    bool signal_received = false;

    while (true)
    {
        wait();

        if (input.event())
        {
            value_buffer[write_ptr] = input.read();
            data_valid_buffer[write_ptr] = true;
            signal_received = true;
        }

        if (clk.posedge())
        {
            if (signal_received == false)
            {
                data_valid_buffer[write_ptr.read()] = false;
            }
            signal_received = false;
            increase_ptr(write_ptr);
        }
    }

}

//******************************************************************************
template <typename signal_t>
void sc_delay_signal<signal_t>::write_output()
{
    while (true)
    {
        wait();

        if (data_valid_buffer[read_ptr.read()] == true)
        {
            delayed.write(value_buffer[read_ptr.read()]);
        }

        increase_ptr(read_ptr);
    }

}

//******************************************************************************
template <typename signal_t>
void sc_delay_signal<signal_t>::zero_delay()
{
    while (true)
    {
        wait();

        delayed.write(input.read());
    }

}

//******************************************************************************
template <typename signal_t>
void sc_delay_signal<signal_t>::increase_ptr(sc_signal<unsigned int>& ptr)
{
    if (ptr.read() >= (delay_cycles-1))
    {
        ptr.write(0);
    }
    else
    {
        ptr.write(ptr.read()+1);
    }

    return;
}
