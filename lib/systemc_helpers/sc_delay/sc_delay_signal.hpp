/*!
 * @file sc_delay_signal.hpp
 * @author Christian Amstutz
 * @date Apr 4, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

/*!
 * @brief
 */
template <typename signal_t, unsigned int delay_cycles>
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

    std::array<bool, delay_cycles> data_valid_buffer;
    std::array<signal_t, delay_cycles> value_buffer;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_output();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    /*!
     * Constructor:
     */
    sc_delay_signal(sc_module_name _name);
    SC_HAS_PROCESS(sc_delay_signal);

private:
    void increase_ptr(sc_signal<unsigned int>& ptr);
};

//******************************************************************************

//******************************************************************************
/*!
 * @class sc_delay_signal
 *
 * The module is sensitive to ....
 */
template <typename signal_t, unsigned int delay_cycles>
sc_delay_signal<signal_t, delay_cycles>::sc_delay_signal(sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        input("input"),
        delayed("delayed"),
        input_signal("input_singal"),
        signal_received("signal_received"),
        read_ptr("read_ptr"),
        write_ptr("write_ptr")
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << input << clk.pos();
    SC_THREAD(write_output);
        sensitive << clk.pos();

    // ----- Module variable initialization ------------------------------------
    read_ptr.write(1);
    write_ptr.write(0);

    for (auto& data_valid_element : data_valid_buffer)
    {
        data_valid_element = false;
    }

    // ----- Module instance / channel binding ---------------------------------

    return;
}

//******************************************************************************
template <typename signal_t, unsigned int delay_cycles>
void sc_delay_signal<signal_t, delay_cycles>::read_input()
{
    while (true)
    {
        wait();

        if (clk.posedge())
        {
            if (!signal_received)
            {
                data_valid_buffer[write_ptr.read()] = false;
            }
            else
            {
                value_buffer[write_ptr] = input_signal.read();
                data_valid_buffer[write_ptr.read()] = true;
            }

            increase_ptr(write_ptr);
            signal_received = false;
        }

        if (input.event())
        {
            input_signal.write(input.read());
            signal_received = true;
        }
    }

}

//******************************************************************************
template <typename signal_t, unsigned int delay_cycles>
void sc_delay_signal<signal_t, delay_cycles>::write_output()
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
template <typename signal_t, unsigned int delay_cycles>
void sc_delay_signal<signal_t, delay_cycles>::increase_ptr(
        sc_signal<unsigned int>& ptr)
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
