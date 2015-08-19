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
    sc_signal<signal_t> input_signal;
    sc_signal<bool> signal_received;
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
        input_signal("input_singal"),
        signal_received("signal_received"),
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
    read_ptr.write(1);
    write_ptr.write(0);

    data_valid_buffer.resize(delay_cycles, false);
    value_buffer.resize(delay_cycles, signal_t());

    // ----- Module instance / channel binding ---------------------------------

    return;
}

//******************************************************************************
template <typename signal_t>
void sc_delay_signal<signal_t>::read_input()
{
    signal_received.write(false);

    while (true)
    {
        wait();

        if (clk.posedge())
        {
            if (!signal_received.read())
            {
                data_valid_buffer[write_ptr.read()] = false;
            }
            else
            {
                value_buffer[write_ptr] = input_signal.read();
                data_valid_buffer[write_ptr.read()] = true;
            }

            increase_ptr(write_ptr);
            signal_received.write(false);
        }

        if (input.event())
        {
            input_signal.write(input.read());
            signal_received.write(true);
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
    if (ptr.read() == delay_cycles-1)
    {
        ptr.write(0);
    }
    else
    {
        ptr.write(ptr.read()+1);
    }

    return;
}

//******************************************************************************

//******************************************************************************

template <typename signal_t>
class sc_delay_signal<signal_t, 0> : public sc_module
{
public:

// ----- Port Declarations -----------------------------------------------------
    /** Input port for the clock signal */
    sc_in<bool> clk;

    sc_in<signal_t> input;
    sc_out<signal_t> delayed;

// ----- Local Channel Declarations --------------------------------------------
    sc_signal<signal_t> forward_signal;

// ----- Process Declarations --------------------------------------------------
    void forward_input();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    sc_delay_signal(sc_module_name _name);
    SC_HAS_PROCESS(sc_delay_signal);
};

//******************************************************************************

//******************************************************************************
/*!
 * @class sc_delay_signal
 *
 * The module is sensitive to ....
 */
template <typename signal_t>
sc_delay_signal<signal_t, 0>::sc_delay_signal(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        input("input"),
        delayed("delayed"),
        forward_signal("forward_singal")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(forward_input);
        sensitive << input;

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

//******************************************************************************
template <typename signal_t>
void sc_delay_signal<signal_t, 0>::forward_input()
{
    while (1)
    {
        wait();

        delayed.write(input.read());
    }
}
