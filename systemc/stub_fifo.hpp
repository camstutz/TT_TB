/*!
 * @file stub_fifo.hpp
 * @author Christian Amstutz
 * @date Apr 15, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "TT_configuration.hpp"
#include "data_representations/do_out_data.hpp"

/*!
 * @brief
 */
template <unsigned int depth>
class stub_fifo : public sc_module
{
public:
// ----- Port Declarations -----------------------------------------------------
    sc_in<bool> clk;
    sc_in<bool> rst;

    sc_in<bool> read_en;
    sc_out<bool> not_empty;

    sc_in<do_out_data> stub_in;
    sc_out<do_out_data> stub_out;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<do_out_data> fifo;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_output();
    void update_empty();

// ----- Other Method Declarations ---------------------------------------------

// ----- Module Instantiations -------------------------------------------------

// ----- Constructor -----------------------------------------------------------
    stub_fifo(sc_module_name _name);
    SC_HAS_PROCESS(stub_fifo);

private:
};


// *****************************************************************************

/*!
 * @class stub_fifo
 *
 * The module is sensitive to ....
 */

template <unsigned int depth>
stub_fifo<depth>::stub_fifo(sc_module_name _name) :
        sc_module(_name) ,
        clk("clk"),
        rst("rst"),
        read_en("read_en"),
        not_empty("not_empty"),
        stub_in("stub_in"),
        stub_out("stub_out"),
        fifo("fifo", depth)
{
    // ----- Process registration ----------------------------------------------
    SC_THREAD(read_input);
        sensitive << clk.pos();
    SC_THREAD(write_output);
        sensitive << clk.pos();
    SC_THREAD(update_empty);
        sensitive << fifo.data_read_event() << fifo.data_written_event();

    // ----- Module variable initialization ------------------------------------

    // ----- Module instance / channel binding ---------------------------------

    return;
}

// *****************************************************************************
template <unsigned int depth>
void stub_fifo<depth>::read_input()
{
    while(1)
    {
        wait();

        auto input = stub_in.read();
        if (input.get_dv() == true)
        {
            fifo.write(input);
        }
    }

}

// *****************************************************************************
template <unsigned int depth>
void stub_fifo<depth>::write_output()
{
    while(1)
    {
        wait();

        if (read_en && not_empty)
        {
            auto fifo_value = fifo.read();
            stub_out.write(fifo_value);
        }
        else
        {
            stub_out.write(do_out_data());
        }
    }
}

// *****************************************************************************
template <unsigned int depth>
void stub_fifo<depth>::update_empty()
{
    while (1)
    {
        if (fifo.num_available() == 0)
        {
            not_empty.write(false);
        }
        else
        {
            not_empty.write(true);
        }

        wait();
    }

}
