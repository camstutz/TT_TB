/*!
 * @file stub_fifo.hpp
 * @author Christian Amstutz
 * @date Apr 25, 2014
 *
 * @brief
 *
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#pragma once

#include <systemc.h>

#include "../../../systems/TT_configuration.hpp"
#include "../../../data_formats/fm_out_data.hpp"

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

    sc_in<fm_out_data> stub_in;
    sc_out<fm_out_data> stub_out;

// ----- Local Channel Declarations --------------------------------------------
    sc_fifo<fm_out_data> fifo;

// ----- Process Declarations --------------------------------------------------
    void read_input();
    void write_output();
    void update_not_empty();

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
        sensitive << stub_in;
    SC_THREAD(write_output);
        sensitive << clk.pos();
    SC_THREAD(update_not_empty);
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

        fm_out_data input_value = stub_in.read();
        if (input_value.get_data_valid_flag())
        {
            fifo.write(input_value);
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
            fm_out_data fifo_value = fifo.read();
            stub_out.write(fifo_value);
        }
    }

}

// *****************************************************************************
template <unsigned int depth>
void stub_fifo<depth>::update_not_empty()
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
