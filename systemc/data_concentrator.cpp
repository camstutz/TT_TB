/*!
 * @file data_concentrator.cpp
 * @author Christian Amstutz
 * @date Mar 24, 2014
 *
 * @brief
 */

/*
 *  Copyright (c) 2014 by Christian Amstutz
 */

#include "data_concentrator.hpp"

// *****************************************************************************

// *****************************************************************************

/*!
 * @class data_concentrator
 *
 * The module is sensitive to ....
 */

data_concentrator::data_concentrator(sc_module_name _name) :
        sc_module(_name) ,
        clk("clk"),
        rst("rst"),
        fe_stub_in(NR_FE_CHIP_PER_MODULE, MAX_HITS_PER_FE_CHIP, "stub_in", 1, 1),
        dc_out("dc_out")
{
    // ----- Process registration ------------------------------------------------
    SC_THREAD(advance_clock_phase);
        sensitive << clk.pos();
    SC_THREAD(read_FE_chips);
        sensitive << clk.pos();
    SC_THREAD(write_output);
        sensitive << clk.pos();

    // ----- Module variable initialization --------------------------------------
    clock_phase = 0;

    // ----- Module instance / channel binding -----------------------------------

    // Create and name the input ports

    return;
}

// *****************************************************************************
void data_concentrator::read_FE_chips()
{
    while(1)
    {
        wait();

        for(auto& fe_in : fe_stub_in)
        {
            fe_out_data fe_data = fe_in.read();
            if (fe_data.get_dv() == true)
            {
                dc_out_word::dc_stub_t stub;
                stub.set_timestamp(sc_bv<3>(clock_phase.read()));
                auto signal_key = fe_stub_in.get_key(fe_in);
                stub.set_fechip(sc_bv<3>(signal_key.second.Y_dim));
                stub.set_strip(fe_data.get_data().get_strip());
                stub.set_bend(fe_data.get_data().get_bend());

                dc_out_word data_word = dc_out_word(true, stub);

                stub_buffer.push_back(data_word);
            }
        }
    }

}

// *****************************************************************************
void data_concentrator::advance_clock_phase()
{
    while (1)
    {
        wait();

        if (clock_phase.read() == NR_DC_WINDOW_CYCLES-1)
        {
            clock_phase.write(0);
        }
        else
        {
            clock_phase.write(clock_phase.read()+1);
        }

        if (clock_phase.read() == NR_DC_WINDOW_CYCLES-1)
        {
            create_output_buffer();
        }
    }

}

// *****************************************************************************
void data_concentrator::write_output() {

    //! todo: change constants numbers to parameter
    while(1)
    {
        wait();

        sc_bv<DC_OUTPUT_WIDTH> output_val;
        unsigned int high_buffer = (clock_phase.read()+1)*(DC_OUTPUT_WIDTH-2)-1;
        unsigned int low_buffer = clock_phase.read()*(DC_OUTPUT_WIDTH-2);
        output_val(DC_OUTPUT_WIDTH-3,0) = output_buffer(high_buffer, low_buffer);
        output_val[DC_OUTPUT_WIDTH-2] = 0;

        // Indicate the beginning of a window by the first bit of a data word
        if (clock_phase.read() == 0)
        {
            output_val[DC_OUTPUT_WIDTH-1] = 1;
        }
        else
        {
            output_val[DC_OUTPUT_WIDTH-1] = 0;
        }

        dc_out.write(output_val);
    }

}

// *****************************************************************************
void data_concentrator::create_output_buffer()
{
    output_buffer = sc_bv<DC_OUTPUT_WIDTH*NR_DC_WINDOW_CYCLES>(0);

    // Buffer size is maximal NR_DC_OUT_STUBS in real system
    if (stub_buffer.size() > NR_DC_OUT_STUBS)
    {
        std::cout << "data_concentrator: Stub buffer overflow!" << std::endl;
    }
    stub_buffer.resize(NR_DC_OUT_STUBS, dc_out_word());

    for(unsigned short i; i<NR_DC_OUT_STUBS; i++)
    {
        output_buffer( (i+1)*dc_out_word::width-1, i*dc_out_word::width) =
                stub_buffer[i].get_bit_vector();
    }

    stub_buffer.clear();

    return;
}
